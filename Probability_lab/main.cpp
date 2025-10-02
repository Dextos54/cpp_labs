#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <vector>


// ===== Базовый интерфейс =====
class RandomVariable {
public:
    virtual unsigned roll() = 0;
    virtual ~RandomVariable() = default;
};

// ===== Dice =====
class Dice : public RandomVariable {
public:
    Dice(unsigned max, unsigned seed)
        : max(max), dstr(1, max), reng(seed) {}

    unsigned roll() override {
        return dstr(reng);
    }

private:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

// ===== ThreeDicePool =====
class ThreeDicePool : public RandomVariable {
public:
    ThreeDicePool(RandomVariable &d1, RandomVariable &d2, RandomVariable &d3)
        : d1(d1), d2(d2), d3(d3) {}

    unsigned roll() override {
        return d1.roll() + d2.roll() + d3.roll();
    }

private:
    RandomVariable &d1, &d2, &d3;
};

// ===== универсальное матожидание =====
double expected_value(RandomVariable &rv, unsigned number_of_rolls = 1) {
    unsigned long long accum = 0;
    for (unsigned cnt = 0; cnt < number_of_rolls; ++cnt)
        accum += rv.roll();
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

// ===== PenaltyDice =====
class PenaltyDice : public RandomVariable {
public:
    PenaltyDice(RandomVariable &base) : base(base) {}
    unsigned roll() override {
        auto r1 = base.roll();
        auto r2 = base.roll();
        return std::min(r1, r2);
    }
private:
    RandomVariable &base;
};

// ===== BonusDice =====
class BonusDice : public RandomVariable {
public:
    BonusDice(RandomVariable &base) : base(base) {}
    unsigned roll() override {
        auto r1 = base.roll();
        auto r2 = base.roll();
        return std::max(r1, r2);
    }
private:
    RandomVariable &base;
};

// ===== вероятность выпадения конкретного значения =====
double value_probability(unsigned value, RandomVariable &rv, unsigned number_of_rolls = 1) {
    unsigned count = 0;
    for (unsigned i = 0; i < number_of_rolls; ++i) {
        if (rv.roll() == value) ++count;
    }
    return static_cast<double>(count) / number_of_rolls;
}

// ===== DoubleDice (множественное наследование) =====
class DoubleDice_Multi : public PenaltyDice, public BonusDice {
public:
    DoubleDice_Multi(RandomVariable &base)
        : PenaltyDice(base), BonusDice(base), base(base) {}

    unsigned roll() override {
        auto r1 = PenaltyDice::roll();
        auto r2 = BonusDice::roll();
        return (r1 + r2) / 2;
    }
private:
    RandomVariable &base;
};

// ===== DoubleDice (композиция) =====
class DoubleDice_Compose : public RandomVariable {
public:
    DoubleDice_Compose(RandomVariable &base)
        : penalty(base), bonus(base) {}

    unsigned roll() override {
        auto r1 = penalty.roll();
        auto r2 = bonus.roll();
        return (r1 + r2) / 2;
    }

private:
    PenaltyDice penalty;
    BonusDice bonus;
};


void build_histogram(RandomVariable& r, const std::string& filename, 
                    unsigned min_value, unsigned max_value, 
                    unsigned num_rolls = 50000) {
    std::vector<unsigned> counts(max_value - min_value + 1, 0);
    
    for (unsigned i = 0; i < num_rolls; ++i) {
        unsigned result = r.roll();
        if (result >= min_value && result <= max_value) {
            counts[result - min_value]++;
        }
    }
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    
    
    file << "value,probability,count\n";
    
    for (unsigned value = min_value; value <= max_value; ++value) {
        unsigned index = value - min_value;
        double probability = static_cast<double>(counts[index]) / num_rolls;
        file << value << "," << probability << "," << counts[index] << "\n";
    }
    
    file.close();
    
}





// ===== main =====
int main() {
    // --- Задание 1 ---
    Dice d(6, 40);
    std::cout << "E[Dice] ~ " << expected_value(d, 1000000) << "\n";

    Dice d1(6, 1), d2(6, 2), d3(6, 3);
    ThreeDicePool pool(d1, d2, d3);
    std::cout << "E[ThreeDicePool] ~ " << expected_value(pool, 1000000) << "\n\n";

    // --- Задание 2 ---
    Dice d100(100, 123);

    PenaltyDice pd(d100);
    BonusDice bd(d100);

    std::cout << "P(X=50) Dice ≈ " << value_probability(50, d100, 1000000) << "\n";
    std::cout << "P(X=50) Penalty ≈ " << value_probability(50, pd, 1000000) << "\n";
    std::cout << "P(X=50) Bonus ≈ " << value_probability(50, bd, 1000000) << "\n\n";

    // --- Задание 3 ---
    DoubleDice_Multi ddm(d100);
    DoubleDice_Compose ddc(d100);

    //std::cout << "E[DoubleDice_Multi] ~ " << expected_value(ddm, 1000000) << "\n";
    std::cout << "E[DoubleDice_Compose] ~ " << expected_value(ddc, 1000000) << "\n";

    std::random_device rd;
    
    // Для Dice [1,100]
    PenaltyDice penaltyD100(d100);
    BonusDice bonusD100(d100);
    
    build_histogram(d100, "data/normal_dice_1_100.csv", 1, 100);
    build_histogram(penaltyD100, "data/penalty_dice_1_100.csv", 1, 100);
    build_histogram(bonusD100, "data/bonus_dice_1_100.csv", 1, 100);
    
    // Для ThreeDicePool [3,18]
    ThreeDicePool threeD6(d1, d2, d3);
    PenaltyDice penaltyThreeD6(threeD6);
    BonusDice bonusThreeD6(threeD6);
    
    build_histogram(threeD6, "data/normal_threeD6_3_18.csv", 3, 18);
    build_histogram(penaltyThreeD6, "data/penalty_threeD6_3_18.csv", 3, 18);
    build_histogram(bonusThreeD6, "data/bonus_threeD6_3_18.csv", 3, 18);
    DoubleDice_Compose doubleD100(d100);
    build_histogram(doubleD100, "data/double_dice_2_100.csv", 2, 100);
}

