#pragma once

#include <iostream>
namespace cpp_playground
{
    template <typename T>
    class shared_ptr
    {
    public:
        shared_ptr()
        {
        }

        ~shared_ptr()
        {
            clean_up();
        }

        explicit shared_ptr(T *ptr) : m_ref_count(new size_t), m_ptr(ptr)
        {
            (*m_ref_count) = 1;
        }

        shared_ptr(const shared_ptr<T> &other) : m_ref_count(other.m_ref_count), m_ptr(other.m_ptr)
        {
            if (m_ref_count != nullptr)
                (*m_ref_count)++;
        }

        shared_ptr(shared_ptr<T> &&other) : m_ref_count(other.m_ref_count), m_ptr(other.m_ptr)
        {
            other.m_ref_count = nullptr;
            other.m_ptr = nullptr;
        }

        shared_ptr<T> &operator=(const shared_ptr<T> &other) noexcept
        {
            if (this == &other)
                return *this;

            clean_up();

            m_ref_count = other.m_ref_count;
            m_ptr = other.m_ptr;
            if (m_ref_count != nullptr)
                (*m_ref_count)++;
        }

        shared_ptr<T> &operator=(shared_ptr<T> &&other) noexcept
        {
            if (this == &other)
                return *this;

            clean_up();

            m_ref_count = other.m_ref_count;
            m_ptr = other.m_ptr;

            other.m_ref_count == nullptr;
            other.m_ptr == nullptr;

            return *this;
        }

        T *get() const
        {
            return m_ptr;
        }

        size_t use_count() const
        {
            if (m_ref_count == nullptr)
                return 0;

            return *m_ref_count;
        }

        T *operator->() const
        {
            return m_ptr;
        }

        T &operator*() const
        {
            return *m_ptr;
        }

    private:
        void clean_up()
        {
            if (m_ref_count == nullptr)
                return;

            (*m_ref_count)--;

            if ((*m_ref_count) != 0)
                return;
            delete m_ref_count;
            delete m_ptr;
        }

    private:
        size_t *m_ref_count = nullptr;
        T *m_ptr = nullptr;
    };
} // namespace cpp_playground

class A
{
public:
    A(std::string data) : m_ptr(data)
    {
        std::cout << m_ptr << " Constructed\n";
    }

    ~A()
    {
        std::cout << m_ptr << " Destructed\n";
    }

    std::string data() const
    {
        return m_ptr;
    }

private:
    std::string m_ptr;
};

void testSharedPtr()
{
    {
        cpp_playground::shared_ptr<A> s1;
        cpp_playground::shared_ptr<A> s2(new A("First"));
        {
            cpp_playground::shared_ptr<A> s3(s2);
            std::cout << "S3 count " << s3.use_count() << "\n";
        }
        std::cout << "S1 count " << s2.use_count() << "\n";

        auto s4 = s2;
        std::cout << "S4 count " << s4.use_count() << "\n";

        auto s5(std::move(s2));

        std::cout << "S2 count " << s2.use_count() << "\n";
        std::cout << "S5 count " << s5.use_count() << "\n";

        auto s6 = std::move(s4);
        std::cout << "S4 count " << s4.use_count() << "\n";
        std::cout << "S6 count " << s6.use_count() << "\n";
    }
}
