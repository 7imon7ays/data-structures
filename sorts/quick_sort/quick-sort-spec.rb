require_relative './quick-sort.rb'
require 'rspec'

describe "quick sort" do
  it "sorts an empty array" do
    empty = []
    quick_sort! empty
    empty.should == []
  end

  it "sorts a one element array" do
    one_element = [1]
    quick_sort! one_element
    one_element.should == [1]
  end

  it "sorts an even number of elements" do
    even_number = (1..20).to_a.shuffle
    quick_sort! even_number
    even_number.should == (1..20).to_a
  end

  it "sorts an odd number of elements" do
    odd_number = (1..23).to_a.shuffle
    quick_sort! odd_number
    odd_number.should == (1..23).to_a
  end

  it "sorts duplicate elements" do
    duplicates = [3, 3, 2, 1, 2, 1]
    quick_sort! duplicates
    duplicates.should == [1, 1, 2, 2, 3, 3]
  end
end

