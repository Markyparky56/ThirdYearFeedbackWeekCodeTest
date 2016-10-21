#include <cstdint>
#include <iostream>
#include <array>
#include <unordered_map>

class Currency
{
public:
    enum class Type {
                     // coins
                     cent50 = 0,
                     euro1 = 1,
                     euro2 = 2,
                     penny50 = 3,
                     pound1 = 4,
                     // notes
                     euro5 = 0,
                     euro10 = 1,
                     euro100 = 2,
                     pound5 = 3,
                     pound10 = 4
                    };
    Currency(Type InType, float InWeight)
        : type(InType)
        , weight(InWeight)
    {}
    float GetWeight() { return weight; }
    Type GetType() { return type; }

    static bool IsCoin(Currency::Type type)
    {
        return (type == Type::cent50 || type == Type::euro1 || type == Type::euro2 || type == Type::penny50 || type == Type::pound1);
    }
    static bool IsNote(Currency::Type type)
    {
        return !IsCoin(type);
    }
protected:
    float weight;
    Type type;
};

// These would be better as vectors, but the question asked for arrays
static std::array<Currency, 5> coins
{
    Currency(Currency::Type::cent50, 0.01f),
    Currency(Currency::Type::euro1, 0.1f),
    Currency(Currency::Type::euro2, 1.0f),
    Currency(Currency::Type::penny50, 0.01f),
    Currency(Currency::Type::pound1, 0.1f)
};

static std::array<Currency, 5> notes
{
    Currency(Currency::Type::euro5, 0.001f),
    Currency(Currency::Type::euro10, 0.005f),
    Currency(Currency::Type::euro100, 0.009f),
    Currency(Currency::Type::pound5, 0.001f),
    Currency(Currency::Type::pound10, 0.005f)
};

class Wallet
{
public:
    Wallet() {}
    Wallet(std::unordered_map<Currency::Type, int> InContents)
        : contents(InContents)
    {}

    void AddCurrency(Currency::Type type, int num)
    {
        auto prev = contents.find(type);
        if (prev == contents.end())
        {
            num += prev->second;
            contents.erase(prev);
        }
        contents.insert(std::make_pair(type, num));
    }

    int GetAmount(Currency::Type type)
    {
        auto currencyType = contents.find(type);
        if (currencyType != contents.end())
        {
            return currencyType->second;
        }
        else
        {
            return 0;
        }
    }

    float GetWeight()
    {
        float weight = 0.0f;
        for (auto iter = contents.begin(); iter != contents.end(); iter++)
        {
            if (Currency::IsCoin(iter->first))
            {
                weight += iter->second * coins[static_cast<int>(iter->first)].GetWeight();
            }
            else // Notes
            {
                weight += iter->second * notes[static_cast<int>(iter->first)].GetWeight();
            }
        }
        return weight;
    }

protected:
    std::unordered_map<Currency::Type, int> contents;
};

int main()
{
    Wallet tomsWallet({
                        {Currency::Type::cent50, 1},
                        {Currency::Type::euro10, 1},
                        {Currency::Type::euro100, 1}
                      });
    Wallet jacksWallet({
                        {Currency::Type::penny50, 1},
                        {Currency::Type::euro10, 1},
                        {Currency::Type::pound5, 1}
                      });

    std::cout << "Tom's wallet contains " << tomsWallet.GetWeight() << "g in currency" << std::endl;
    std::cout << "Jack's wallet contains " << jacksWallet.GetWeight() << "g in currency" << std::endl;

    return 0;
}
