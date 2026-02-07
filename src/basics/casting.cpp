
class Book
{
public:
    explicit Book(int a) : m_val(a) {}
    [[nodiscard]] constexpr auto len() const
    {
        return m_val;
    }

private:
    int m_val;
};

int main()
{
    Book const b(10);

    return 0;
}
