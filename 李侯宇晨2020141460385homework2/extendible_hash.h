/*
 * extendible_hash.h : implementation of in-memory hash table using extendible
 * hashing
 *
 * Functionality: The buffer pool manager must maintain a page table to be able
 * to quickly map a PageId to its corresponding memory location; or alternately
 * report that the PageId does not match any currently-buffered page.
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <mutex>

#include "hash/hash_table.h"
using namespace std;


namespace cmudb {


template <typename K, typename V>
class ExtendibleHash : public HashTable<K, V> {
  struct Bucket {
    Bucket(int depth) : localDepth(depth) {};
    int localDepth;
    map<K, V> kmap;
    mutex latch;
  };
public:
  // constructor
  ExtendibleHash(size_t size);
  ExtendibleHash();
  // helper function to generate hash addressing
  size_t HashKey(const K &key) const;
  // helper function to get global & local depth
  int GetGlobalDepth() const;
  int GetLocalDepth(int bucket_id) const;
  int GetNumBuckets() const;
  // lookup and modifier
  bool Find(const K &key, V &value) override;
  bool Remove(const K &key) override;
  void Insert(const K &key,const V &value) override;

//为了方便其它函数的实现，增加一个得到桶的id的辅助方法
  int getIdx(const K &key) const;

private:
  // add your own member variables here
  int globalDepth;
  size_t bucketSize;  //每个桶装能多少数据
  int bucketNum;
    // buckets是整个顶层的索引，里面装的是每一个桶
  vector<shared_ptr<Bucket>> buckets;
  mutable mutex latch;
};
} // namespace cmudb
