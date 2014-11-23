require_relative './quick-sort.rb'
require 'rspec'

describe "quick sort" do
  it "sorts an empty array" do
    empty = []
    quick_sort! empty
    expect(empty).to be_empty
  end

  it "sorts a one element array" do
    one_element = [1]
    quick_sort! one_element
    expect(one_element).to eq [1]
  end

  it "sorts an even number of elements" do
    even_number = (1..20).to_a.shuffle
    quick_sort! even_number
    expect(even_number).to eq (1..20).to_a
  end

  it "sorts an odd number of elements" do
    odd_number = (1..23).to_a.shuffle
    quick_sort! odd_number
    expect(odd_number).to eq (1..23).to_a
  end

  it "sorts duplicate elements" do
    duplicates = [3, 3, 2, 1, 2, 1]
    quick_sort! duplicates
    expect(duplicates).to eq duplicates.sort
  end

  it "sorts elements in a specified order" do
    elements = (1..10).to_a.shuffle
    quick_sort!(elements) { |a, b| a > b }
    expect(elements).to eq (1..10).to_a.reverse
  end
end

