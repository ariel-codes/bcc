//
// Created by Ariel Santos on 07/03/21.
//
#include <stdexcept>
#include <fstream>
#include <cassert>
#include <iostream>

#include <benchmark/benchmark.h>

#include "Array.hpp"
#include "sorting.hpp"

class SortFixture : public benchmark::Fixture {
 public:
  Array aleatorio = loadFile("dados_aleatorio.txt"),
	  crescente = loadFile("dados_crescente.txt"),
	  descrescente = loadFile("dados_descrescente.txt");
  Array to_sort{0};

  void SetUp(::benchmark::State &state) override {
	Array view(state.range(0));
	Array *data;
	switch (state.range(1)) {
	  case 0: data = &aleatorio;
		break;
	  case 1: data = &crescente;
		break;
	  case 2: data = &descrescente;
	}
	std::copy(data->items, data->items + state.range(0), view.items);
	to_sort = view;
  }

  void TearDown(::benchmark::State &st) override {}
 private:
  static Array loadFile(const std::string &filename) {
	Array data(200000);
	std::ifstream file(filename);
	for (size_t i = 0; i < data.size; ++i) {
	  std::string name;
	  distance_t distance;
	  assert((file[i] >> name >> distance) && "Arquivo mal-formado");
	  data[i] = BaseDistancia(name, distance);
	}
	return data;
  }
};

BENCHMARK_DEFINE_F(SortFixture, Insertion)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::insertion(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Insertion)
->ArgsProduct({{100, 500, 1000, 5000, 10000, 50000, 100000, 200000}, {0, 1, 2}});

BENCHMARK_DEFINE_F(SortFixture, Merge)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::merge(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Merge)
->ArgsProduct({{100, 500, 1000, 5000, 10000, 50000, 100000, 200000}, {0, 1, 2}});

BENCHMARK_DEFINE_F(SortFixture, Quick)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::quick(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Quick)
->ArgsProduct({{100, 500, 1000, 5000, 10000, 50000, 100000, 200000}, {0, 1, 2}});

BENCHMARK_DEFINE_F(SortFixture, QuickMed3)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::quick_med3(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, QuickMed3)
->ArgsProduct({{100, 500, 1000, 5000, 10000, 50000, 100000, 200000}, {0, 1, 2}});

BENCHMARK_DEFINE_F(SortFixture, Cycle)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::cycle(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Cycle)
->ArgsProduct({{100, 500, 1000, 5000, 10000}, {0, 1, 2}});

BENCHMARK_MAIN();