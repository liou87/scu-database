/**
 * lru_replacer.h
 *
 * Functionality: The buffer pool manager must maintain a LRU list to collect
 * all the pages that are unpinned and ready to be swapped. The simplest way to
 * implement LRU is a FIFO queue, but remember to dequeue or enqueue pages when
 * a page changes from unpinned to pinned, or vice-versa.
 */

#pragma once


#include <memory>
#include <unordered_map>
#include <mutex>
#include "buffer/replacer.h"

using namespace std;
namespace cmudb {

template <typename T> class LRUReplacer : public Replacer<T> {
  struct Node {
    Node() {};
    Node(T val) : val(val) {};
    T val;
    shared_ptr<Node> prev;   //指向前一个节点
    shared_ptr<Node> next;   //指向后一个节点
  };
public:
  // do not change public interface
  LRUReplacer();

  ~LRUReplacer();

  void Insert(const T &value);

  bool Victim(T &value);

  bool Erase(const T &value);

  size_t Size();

private:
  shared_ptr<Node> head;   //头节点
  shared_ptr<Node> tail;    //尾节点
   //unordered_map里装的是无序的数据，数据通过key来查找
  unordered_map<T,shared_ptr<Node>> map;  
  mutable mutex latch;
  // add your member variables here
};

} // namespace cmudb
