#!/usr/bin/env ruby

require 'open3'

class String
	def black;          "\e[30m#{self}\e[0m" end
	def red;            "\e[31m#{self}\e[0m" end
	def green;          "\e[32m#{self}\e[0m" end

	def bold;           "\e[1m#{self}\e[22m" end
	def italic;         "\e[3m#{self}\e[23m" end
end

puts "[TESTING] relacao.c \n".bold

err, status = Open3.capture2e('gcc relacao.c')
unless status.success?
	puts "[FAIL] Compile".red
	puts err
	exit
end
puts "[PASS] Compile".green
