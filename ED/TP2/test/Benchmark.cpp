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
  Array data{200000};
  Array to_sort{0};

  SortFixture() {
	std::ifstream file("dados_aleatorio.txt");
	for (size_t i = 0; i < data.size; ++i) {
	  std::string name;
	  distance_t distance;
	  assert((file >> name >> distance) && "Arquivo mal-formado");
	  data[i] = BaseDistancia(name, distance);
	}
  }

  void SetUp(::benchmark::State &state) override {
	Array view(state.range(0));
	std::copy(data.items, data.items + state.range(0), view.items);
	to_sort = view;
  }

  void TearDown(::benchmark::State &st) override {}

};

BENCHMARK_DEFINE_F(SortFixture, Insertion)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::insertion(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Insertion)
->Arg(100)->Arg(500)->Arg(1000)->Arg(5000)->Arg(10000)->Arg(50000)->Arg(100000)->Arg(200000);

BENCHMARK_DEFINE_F(SortFixture, Merge)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::merge(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Merge)
->Arg(100)->Arg(500)->Arg(1000)->Arg(5000)->Arg(10000)->Arg(50000)->Arg(100000)->Arg(200000);

BENCHMARK_DEFINE_F(SortFixture, Quick)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::quick(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Quick)
->Arg(100)->Arg(500)->Arg(1000)->Arg(5000)->Arg(10000)->Arg(50000)->Arg(100000)->Arg(200000);

BENCHMARK_DEFINE_F(SortFixture, QuickMed3)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::quick_med3(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, QuickMed3)
->Arg(100)->Arg(500)->Arg(1000)->Arg(5000)->Arg(10000)->Arg(50000)->Arg(100000)->Arg(200000);

BENCHMARK_DEFINE_F(SortFixture, Cycle)(benchmark::State &state) {
  for (auto _ : state) {
	sorting::cycle(to_sort);
  }
}
BENCHMARK_REGISTER_F(SortFixture, Cycle)
->Arg(100)->Arg(500)->Arg(1000)->Arg(5000)->Arg(10000)->Arg(50000)->Arg(100000)->Arg(200000);

BENCHMARK_MAIN();