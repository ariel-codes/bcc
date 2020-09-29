#!/usr/bin/env ruby

require 'open3'

class String
  def black
    "\e[30m#{self}\e[0m"
  end

  def red
    "\e[31m#{self}\e[0m"
  end

  def green
    "\e[32m#{self}\e[0m"
  end

  def bold
    "\e[1m#{self}\e[22m"
  end

  def italic
    "\e[3m#{self}\e[23m"
  end
end

PROP_REGEX = /
    Reflexiva:\s(?<reflexiva>[VF]).+
    Irreflexiva:\s(?<irreflexiva>[VF]).+
    Simétrica:\s(?<simetrica>[VF]).+
    Anti-simétrica:\s(?<antissimetrica>[VF]).+
    Assimétrica:\s(?<assimetrica>[VF]).+
    Transitiva:\s(?<transitiva>[VF]).+
    Relação\sde\sequivalência:\s(?<equivalencia>[VF]).+
    Relação\sde\sordem\sparcial:\s(?<ordem>[VF])
  /xm.freeze

PAIRS_REGEX = /((?:\(\d+,\d+\); ?)+)/.freeze
PAIR_REGEX = /(\d+,\d+)/.freeze

puts "[TESTING] relacao.c \n".bold

err, status = Open3.capture2e 'gcc relacao.c'
unless status.success?
  puts '[FAIL] Compile'.red
  puts err
  exit
end
puts '[PASS] Compile'.green

9.times do |index| # rubocop:disable Metrics/BlockLength
  puts "Example ##{index + 1}"
  input = File.read "exemplos/ex#{index + 1}.txt"
  out_ref = File.read "exemplos/sd#{index + 1}.txt"
  out_test, = Open3.capture2e './a.out', stdin_data: input

  properties_ref = out_ref.match(PROP_REGEX).named_captures
  properties_test = out_test.match(PROP_REGEX).named_captures
  if properties_ref == properties_test
    puts "\t[PASS] Properties".green
  else
    puts "\t[FAIL] Properties".red
    properties_ref.each do |key, val|
      puts "\t\t#{key.upcase}: Expected #{val}, got #{properties_test[key]}" if val != properties_test[key]
    end
  end

  pairs_ref = out_ref.scan(PAIRS_REGEX).flatten
  pairs_test = out_test.scan(PAIRS_REGEX).flatten
  pairs_ref.each_with_index do |pairs, index|
    points_ref = pairs&.scan(PAIR_REGEX)&.flatten&.sort || []
    points_test = pairs_test[index]&.scan(PAIR_REGEX)&.flatten&.sort || []
    if points_ref == points_test
      puts "\t[PASS] Pairs (#{index})".green
    else
      puts "\t[FAIL] Pairs (#{index})".red
      missing = points_ref - points_test
      puts "\t\tMissing: #{missing}" if missing
      misplaced = points_test - points_ref
      puts "\t\tMisplaced: #{misplaced}"
    end
  end
end
