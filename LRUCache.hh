/**
 * 
 * LRUCache.hh - Modern C++ Implementation of LRU Cache
 *
 */

#ifndef _LRU_CACHE_HH_
#define _LRU_CACHE_HH_

#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstddef>

template<typename K, typename V>
class LRUCache {
public:

  using CacheItem = std::pair<K, V>;
  using CacheItemListIterator = typename std::list<CacheItem>::iterator;

  LRUCache(size_t max_size) : max_size_(max_size) {}

  void put(const K& key, const V& value) {
    auto it = cache_item_map_.find(key);
    cache_item_list_.push_front(CacheItem{key, value});
    if (it != cache_item_map_.end()) {
      cache_item_list_.erase(it->second);
      cache_item_map_.erase(it);
    }
    cache_item_map_[key] = cache_item_list_.begin();

    if (cache_item_map_.size() > max_size_) {
      auto last = cache_item_list_.end();
      --last;
      cache_item_map_.erase(last->first);
      cache_item_list_.pop_back();
    }
  }

  const V& get(const K& key) {
    auto it = cache_item_map_.find(key);
    if (it == cache_item_map_.end()) {
      throw std::range_error("There is no such key in cache");
    } else {
      cache_item_list_.splice(cache_item_list_.begin(), cache_item_list_, it->second);
      return it->second->second;
    }
  }

  bool exists(const K& key) const { return cache_item_map_.find(key) != cache_item_map_.end(); }
  size_t size() const { return cache_item_map_.size(); }

private:
  std::list<CacheItem> cache_item_list_;
  std::unordered_map<K, CacheItemListIterator> cache_item_map_;
  size_t max_size_;

};

#endif
