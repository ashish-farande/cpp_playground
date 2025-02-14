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
            if (m_ref_count == nullptr)
                return;

            (*m_ref_count)--;

            if ((*m_ref_count) != 0)
                return;

            delete m_ref_count;
            delete m_data;
        }

        explicit shared_ptr(T *ptr) : m_ref_count(new size_t), m_data(ptr)
        {
            (*m_ref_count) = 1;
        }

        shared_ptr(const shared_ptr<T> &other) : m_ref_count(other.m_ref_count), m_data(other.m_data)
        {
            if (m_ref_count != nullptr)
                (*m_ref_count)++;
        }

        shared_ptr(const shared_ptr<T> &&other) : m_ref_count(other.m_ref_count), m_data(other.m_data) 
        {
            other.m_ref_count == nullptr;
            other.m_data == nullptr;
        }

        shared_ptr<T> &operator=(const shared_ptr<T> &other) noexcept
        {
            if (this == &other)
                return *this;

            if (m_ref_count != nullptr)
            {
                (*m_ref_count)--;

                if ((*m_ref_count) == 0)
                {
                    delete m_ref_count;
                    delete m_data;
                }
            }

            m_ref_count = other.m_ref_count;
            m_data = other.m_data;
            if (m_ref_count != nullptr)
                (*m_ref_count)++;
        }

        shared_ptr<T> &operator=(const shared_ptr<T> &&other) noexcept
        {
            if (this == &other)
                return *this;

            if (m_ref_count != nullptr)
            {
                (*m_ref_count)--;

                if ((*m_ref_count) == 0)
                {
                    delete m_ref_count;
                    delete m_data;
                }
            }

            m_ref_count = other.m_ref_count;
            m_data = other.m_data;

            other.m_ref_count == nullptr;
            other.m_data == nullptr;
        }

        T *get() const
        {
            return m_data;
        }

        size_t use_count() const
        {
            if (m_ref_count == nullptr)
                return 0;

            return *m_ref_count;
        }

    private:
        size_t *m_ref_count = nullptr;
        T *m_data = nullptr;
    };
} // namespace cpp_playground

class A
{
public:
    A(std::string data) : m_data(data)
    {
        std::cout << m_data << " Constructed\n";
    }

    ~A()
    {
        std::cout << m_data << " Destructed\n";
    }

    std::string data() const
    {
        return m_data;
    }

private:
    std::string m_data;
};

void testSharedPtr()
{
    cpp_playground::shared_ptr<A> s1;
    cpp_playground::shared_ptr<A> s2(new A("First"));
    {
        cpp_playground::shared_ptr<A> s3(s2);
        std::cout<<"S3 count "<<s3.use_count()<<"\n";
    }
}
