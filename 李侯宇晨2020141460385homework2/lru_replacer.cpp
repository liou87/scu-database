/**
 * LRU implementation
 */
#include "buffer/lru_replacer.h"
#include "page/page.h"

namespace cmudb {

template <typename T> LRUReplacer<T>::LRUReplacer() {
  //构造函数，初始化
  head = make_shared<Node>();
  tail = make_shared<Node>();
  head->next = tail;
  tail->prev = head;
}

template <typename T> LRUReplacer<T>::~LRUReplacer() {}

/*
 * Insert value into LRU
 */
template <typename T> void LRUReplacer<T>::Insert(const T &value) {
  lock_guard<mutex> lck(latch);   //确保多线程安全
  shared_ptr<Node> cur;           //指向当前插入值的指针

  //若队列中存在value,则先将之在队列中去除
  if (map.find(value) != map.end()) {
    cur = map[value];
    shared_ptr<Node> prev = cur->prev;
    shared_ptr<Node> succ = cur->next;
    prev->next = succ;
    succ->prev = prev;
  } else {
    // 若队列中不存在value,则创建一个键为value的新结点
    cur = make_shared<Node>(value);
  }
  shared_ptr<Node> fir = head->next;
  cur->next = fir;
  fir->prev = cur;
  cur->prev = head;
  head->next = cur;
  map[value] = cur;
  return;
}

/* If LRU is non-empty, pop the head member from LRU to argument "value", and
 * return true. If LRU is empty, return false
 */
template <typename T> bool LRUReplacer<T>::Victim(T &value) {
  lock_guard<mutex> lck(latch);
  if (map.empty()) {
    return false;
  }
  shared_ptr<Node> last = tail->prev;
  tail->prev = last->prev;
  last->prev->next = tail;

    //传引用
    //在队列中删除最后一个节点并在value中储存其val
  value = last->val;
  map.erase(last->val);
  return true;
}

/*
 * Remove value from LRU. If removal is successful, return true, otherwise
 * return false
 */
template <typename T> bool LRUReplacer<T>::Erase(const T &value) {
  lock_guard<mutex> lck(latch);
    //若队列中存在key为value的节点，在队列中删除
  if (map.find(value) != map.end()) {
    shared_ptr<Node> cur = map[value];
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
  }
  return map.erase(value);
}

template <typename T> size_t LRUReplacer<T>::Size() {
  lock_guard<mutex> lck(latch);
  return map.size();
}

template class LRUReplacer<Page *>;
// test only
template class LRUReplacer<int>;

} // namespace cmudb
