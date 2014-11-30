require "rspec"

shared_examples "binary search" do
  it "returns a value's index inside a sorted array" do
    arr = (0..20).to_a
    expect(binary_search arr, 5).to eq 5
  end

  it "returns nil when the value isn't in the array" do
    arr = []
    expect(binary_search(arr, 1)).to eq nil
  end

  it "finds any index if the value is duplicated" do
    arr = Array.new 10, 1
    expect(binary_search(arr, 1)).to be_between 0, arr.length - 1
  end
end

