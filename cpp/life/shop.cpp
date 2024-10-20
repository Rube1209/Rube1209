#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// 商品类别：食物类
class Food {
private:
    string name;
    double price;
    int stock; // 商品库存量
    double discount; // 折扣

public:
    Food(const string& n, double p, int s) : name(n), price(p), stock(s), discount(0.0) {}

    string getName() const { return name; }
    double getPrice() const { return price * (1 - discount); } // 计算折扣后的价格
    int getStock() const { return stock; }

    void setDiscount(double d) { discount = d; } // 设置折扣
    double getDiscount() const { return discount; }

    void reduceStock(int quantity) {
        if (stock >= quantity) {
            stock -= quantity;
        } else {
            cout << "Not enough stock for " << name << endl;
        }
    }

    virtual void print() const { // 添加 virtual 关键字
        cout << "Food: " << name << ", Price: $" << price 
             << " (Discount: " << discount * 100 << "%), Stock: " << stock << endl;
    }
};

// 商品类别：水果类
class Fruit : public Food {
public:
    Fruit(const string& name, double price, int stock) : Food(name, price, stock) {}

    void print() const override {
        cout << "Fruit: " << getName() << ", Price: $" << getPrice() 
             << ", Stock: " << getStock() << endl;
    }
};

// 商品类别：果汁类
class Juice : public Food {
public:
    Juice(const string& name, double price, int stock) : Food(name, price, stock) {}

    void print() const override {
        cout << "Juice: " << getName() << ", Price: $" << getPrice() 
             << ", Stock: " << getStock() << endl;
    }
};

// 销售数据分析与管理类
class SellMap {
private:
    map<string, int> itemSoldCount; // 每个商品卖出的数量
    map<string, double> itemRevenue; // 每个商品的总收入
    double currentTotal;  // 当前总金额

public:
    SellMap() : currentTotal(0.0) {}

    // 添加销售记录
    void addSale(const string& item, int quantity, double pricePerUnit) {
        itemSoldCount[item] += quantity;
        itemRevenue[item] += quantity * pricePerUnit;
        currentTotal += quantity * pricePerUnit;  // 更新总金额
    }

    // 打印销售数据
    void printSellMap() const {
        cout << "Sales Data Analysis:" << endl;
        for (const auto& entry : itemSoldCount) {
            string item = entry.first;
            int totalSold = entry.second;
            double revenue = itemRevenue.at(item);
            cout << "Item: " << item << ", Total Sold: " << totalSold 
                 << ", Total Revenue: $" << revenue << endl;
        }
        cout << "Current Total: $" << currentTotal << endl;
    }

    // 自动结账功能
    void autoCheckout() {
        cout << "Auto checkout triggered. Total: $" << currentTotal << endl;
        resetSalesData();
    }

    // 重置销售数据
    void resetSalesData() {
        itemSoldCount.clear();
        itemRevenue.clear();
        currentTotal = 0.0;
    }
};

// 商店类
class Shop {
private:
    vector<Food*> inventory; // 商品库存
    SellMap sellMap;         // 销售记录和分析

public:
    // 添加商品到库存
    void addItem(Food* item) {
        inventory.push_back(item);
    }

    // 显示库存
    void showInventory() const {
        cout << "Shop Inventory:" << endl;
        for (const auto& item : inventory) {
            item->print();
        }
    }

    // 卖出商品
    void sellItem(const string& itemName, int quantity) {
        for (const auto& item : inventory) {
            if (item->getName() == itemName) {
                double pricePerUnit = item->getPrice();
                item->reduceStock(quantity);  // 减少库存
                sellMap.addSale(itemName, quantity, pricePerUnit);
                cout << "Sold " << quantity << " units of " << itemName << endl;
                return;
            }
        }
        cout << "Item not found in inventory." << endl;
    }

    // 结账
    void checkout() {
        sellMap.autoCheckout();
    }

    // 打印销售数据
    void printSalesData() const {
        sellMap.printSellMap();
    }

    // 库存量分析
    void analyzeStock() const {
        cout << "Stock Analysis:" << endl;
        for (const auto& item : inventory) {
            if (item->getStock() > 50) { // 假设库存超过50被认为是长期滞销
                cout << "Item: " << item->getName() << " has high stock: " 
                     << item->getStock() << " units." << endl;
                cout << "Consider setting a discount." << endl;
            }
        }
    }

    // 设置折扣
    void setDiscountForItem(const string& itemName, double discount) {
        for (const auto& item : inventory) {
            if (item->getName() == itemName) {
                item->setDiscount(discount);
                cout << "Set a discount of " << discount * 100 << "% for " << itemName << endl;
                return;
            }
        }
        cout << "Item not found in inventory." << endl;
    }
};

int main() {
    // 创建商店
    Shop shop;

    // 添加商品到库存
    shop.addItem(new Fruit("Apple", 1.2, 100)); // 大量库存的苹果
    shop.addItem(new Fruit("Banana", 0.8, 20));
    shop.addItem(new Juice("Orange Juice", 3.5, 60)); // 大量库存的果汁
    shop.addItem(new Juice("Grape Juice", 4.0, 10));

    // 显示库存
    shop.showInventory();

    // 卖出商品
    shop.sellItem("Apple", 10);
    shop.sellItem("Orange Juice", 5);

    // 打印销售数据
    shop.printSalesData();

    // 结账
    shop.checkout();

    // 库存量分析，提醒降价或折扣
    shop.analyzeStock();

    // 为商品设置折扣
    shop.setDiscountForItem("Apple", 0.20); // 设置20%的折扣

    // 显示折扣后的库存
    shop.showInventory();

    return 0;
}
