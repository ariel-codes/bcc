//
// Created by Ariel Santos on 07/03/21.
//
#include <fstream>
#include <cassert>
#include <cstring>
#include <benchmark/benchmark.h>

#include "Array.hpp"
#include "sorting.hpp"

class SortFixture : public benchmark::Fixture {
 public:
  Array *to_sort{nullptr};

  void SetUp(::benchmark::State &state) override {
	std::string filename;
	switch (state.range(1)) {
	  case 0: filename = "dados_aleatorio.txt";
		break;
	  case 1: filename = "dados_crescente.txt";
		break;
	  case 2: filename = "dados_descrescente.txt";
	}
	to_sort = new Array(state.range(0));
	std::ifstream file(filename);
	for (size_t i = 0; i < state.range(0); ++i) {
	  std::string name;
	  distance_t distance;
	  assert((file[i] >> name >> distance) && "Arquivo mal-formado");
	  (*to_sort)[i] = BaseDistancia(name, distance);
	}
  }

  void TearDown(::benchmark::State &st) override {
	delete to_sort;
	to_sort = nullptr;
  }
};

BENCHMARK_DEFINE_F(SortFixture, Insertion)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::insertion(*to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Insertion)
->ArgsProduct({{100, 500, 1000, 5000, 10000, 50000, 100000, 200000}, {0, 1, 2}});

BENCHMARK_DEFINE_F(SortFixture, Merge)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::merge(*to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Merge)
->ArgsProduct({{100, 500, 1000, 5000, 10000, 50000, 100000, 200000}, {0, 1, 2}});

BENCHMARK_DEFINE_F(SortFixture, Quick)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::quick(*to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Quick)
->ArgsProduct({{100, 500, 1000, 5000, 10000, 50000, 100000, 200000}, {0, 1, 2}});

BENCHMARK_DEFINE_F(SortFixture, QuickMed3)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::quick_med3(*to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, QuickMed3)
->ArgsProduct({{100, 500, 1000, 5000, 10000, 50000, 100000, 200000}, {0, 1, 2}});

BENCHMARK_DEFINE_F(SortFixture, Cycle)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::cycle(*to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Cycle)
->ArgsProduct({{100, 500, 1000, 5000}, {0, 1, 2}});

BENCHMARK_DEFINE_F(SortFixture, STD)(benchmark::State &state) {
  for (auto _ : state) {
	std::sort(to_sort->items, &to_sort->end());
  }
}
BENCHMARK_REGISTER_F(SortFixture, STD)
->ArgsProduct({{100, 500, 1000, 5000, 10000, 50000, 100000, 200000}, {0, 1, 2}});

BENCHMARK_MAIN();