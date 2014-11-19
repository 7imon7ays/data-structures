require_relative './merge-sort.rb'
require 'rspec'

describe "merge sort" do
  it "sorts an empty array" do
    empty = []
    merge_sort(empty).should == []
  end

  it "sorts a one element array" do
    one_element = [1]
    merge_sort(one_element).should == [1]
  end

  it "sorts an even number of elements" do
    even_number = (1..20).to_a.shuffle
    merge_sort(even_number).should == (1..20).to_a
  end

  it "sorts an odd number of elements" do
    odd_number = (1..23).to_a.shuffle
    merge_sort(odd_number).should == (1..23).to_a
  end

  it "sorts duplicate elements" do
    duplicates = [3, 3, 2, 1, 2, 1]
    merge_sort(duplicates).should == duplicates.sort
  end
end

