// hash + user-defined list

struct DLinkedNode{
    int key, value;
    DLinkedNode* pre;
    DLinkedNode* next;
    DLinkedNode():key(0),value(0),pre(nullptr),next(nullptr){}
    DLinkedNode(int _key, int _value): key(_key), value(_value), pre(nullptr),next(nullptr){}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int aCapacity;
    int aSize;

    void removeFromList(DLinkedNode* target)
    {
        DLinkedNode* nextNode = target->next;
        DLinkedNode* preNode = target->pre;

        preNode->next = nextNode;
        nextNode->pre = preNode;
    }

    void insertIntoList(DLinkedNode* source)
    {
        DLinkedNode* next = head->next;

        head->next = source;
        source->next = next;

        source->pre = head;
        next->pre = source;
    }    

public:
    LRUCache(int capacity) {
        aCapacity = capacity;
        aSize = 0;
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        if(cache.find(key) != cache.end())
        {
            int aValue = cache[key]->value;
            removeFromList(cache[key]);
            insertIntoList(cache[key]);
            return aValue;
        }
        else
        {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if(cache.find(key) != cache.end())
        {
            cache[key]->value = value;
            removeFromList(cache[key]);
            insertIntoList(cache[key]);
        }
        else
        {
            if(aSize == aCapacity)
            {
                int aKey = tail->pre->key;
                cache.erase(aKey);
                aSize--;
                removeFromList(tail->pre);                
            }
            DLinkedNode* tmp = new DLinkedNode(key, value);
            cache[key] = tmp;
            insertIntoList(cache[key]);
            aSize++;
        }                            
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// hash + STL list

 class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int,int>>::iterator> mp;    
public:
    LRUCache(int capacity):capacity(capacity) {

    }
    
    int get(int key) {
        if(mp.count(key))
        {
            cache.splice(cache.begin(), cache, mp[key]);
            return cache.begin()->second;
        }
        else
        {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if(mp.count(key))
        {            
            cache.splice(cache.begin(), cache, mp[key]);
            auto it = cache.begin();
            it->second = value;
        }
        else
        {
            if(cache.size() == capacity)
            {
                mp.erase(cache.back().first);
                cache.pop_back();
            }
            cache.push_front({key,value});
            mp[key] = cache.begin();                        
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */