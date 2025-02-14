#include <queue>
#include <atomic>
#include <memory>

template <typename T>
class LockFreeQueue
{
private:
    struct Node
    {
        T m_val;
        std::atomic<std::shared_ptr<Node<T>>> m_next = nullptr;

        Node(int val, Node *next = nullptr) : m_val(val), m_next(next) {}
    };
    std::atomic<std::shared_ptr<Node>> head;
    std::atomic<std::shared_ptr<Node>> tail;
    std::atomic<size_t> m_size = 0;

public:
    LockFreeQueue()
    {
        auto dummy = std::make_shared<Node>(T{});
        head.store(dummy);
        tail.store(dummy);
    }

    push(T val)
    {
        auto new_node = std::make_shared<Node>(val);
        std::shared_ptr<Node> old_tail;

        while(true)
        {
            auto old_tail = tail.load();
            auto next = old_tail->next.load();
            if(old_tail == tail.load())
            {
                if(!next)
                {
                    if(old_tail->next.compare_exchange_weak(next, new_node))
                    {
                        tail.compare_exchange_strong(old_tail, new_node);
                        return;
                    }
                }
                else
                {
                    tail.compare_exchange_weak(old_tail, next);
                }
            }
        }
    }

    pop(T val)
    {
        std::shared_ptr<Node> old_head;
        while (true) {
            old_head = head.load();
            auto old_tail = tail.load();
            auto next = old_head->next.load();
            if (old_head == head.load()) { // Ensure head is consistent
                if (old_head == old_tail) {
                    if (!next) {
                        return false; // Queue is empty
                    }
                    tail.compare_exchange_weak(old_tail, next);
                } else {
                    if (head.compare_exchange_weak(old_head, next)) {
                        result = *(next->data);
                        return true;
                    }
                }
            }
        }
    }

};