#include <iostream>
#include <string>
#include <list>
#include <map>
#include <unordered_map>


enum class Side { BUY, SELL };


struct Order {

	uint64_t id;
	double price;
	uint64_t quantity;
	Side side;

};

struct PriceLevel {

	double price;
	std::list<Order> orders;
};

class OrderBook {

private: 
	// Compra: ordenando do Maior para o Menor preço

	std::map<double, PriceLevel, std::greater<double>> buyOrders;

	// Venda: ordenando do Menor para o Maior preço
	std::map<double, PriceLevel, std::less<double>> sellOrders;

	// Mapeamento de ID de ordem para o nível de preço correspondente
	std::unordered_map<uint64_t, std::list<Order>::iterator> orderLookup;


public:

	void addOrder(const Order& order) {

		if (order.side == Side::BUY) {

			buyOrders[order.price].price = order.price;
			buyOrders[order.price].orders.push_back(order);

			// Guarda a referência para cancelamento instantâneo posterior

			orderLookup[order.id] = std::prev(buyOrders[order.price].orders.end());

		}
		else {

			sellOrders[order.price].price = order.price;
			sellOrders[order.price].orders.push_back(order);
			// Guarda a referência para cancelamento instantâneo posterior
			orderLookup[order.id] = std::prev(sellOrders[order.price].orders.end());

		}

		std::cout << "Ordem adicionada com sucesso!" << order.id << '\n';
	}
	};

	int main() {

		OrderBook book;

		// Simular uma ordem de compra

		Order o1 = { 1, 100.5, 10, Side::BUY };

		// Simular uma ordem de venda

		Order o2 = { 2, 101.0, 5, Side::SELL };

		book.addOrder(o1);
		book.addOrder(o2);


		return 0;

	}