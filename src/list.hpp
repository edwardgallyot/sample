#include <cstddef>

namespace utils
{
template <typename type>
class list
{
public:
    list();
    struct node
    {
        type* data;
        node* next = nullptr;
    };

    inline constexpr void add(node* node);
    inline constexpr bool is_empty() const { return this->head == nullptr; }
    inline constexpr size_t get_count() const { return this->count; }
    inline constexpr node const* get_head() const { return this->head; }

private:
    list::node* head;
    size_t count;
};

template<typename type> 
list<type>::list()
:   head(nullptr),
    count(0)
{
}

template<typename type> 
void inline constexpr
list<type>::add(node* n)
{
    if (!n)
    {
        return;
    }

    if (!this->head)
    {
        this->head = n;
        this->count++;
        return;
    }
    node* tmp;
    for (tmp = this->head; tmp != nullptr; tmp = tmp->next) 
    {
        if (tmp->next == nullptr)
        {
            tmp->next = n;
            break;
        }
    }
    this->count++;
}
}

