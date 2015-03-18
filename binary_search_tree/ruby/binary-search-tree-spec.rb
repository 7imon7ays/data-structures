require 'rspec'
require './binary-search-tree.rb'

describe BinarySearchTree do
  subject(:bst) { BinarySearchTree.new [0, 'a'] }
  describe "#insert" do
    it "returns nil if the insertion is redundant" do
      kv_pair = [1, 'b']
      bst.insert kv_pair
      expect(bst.insert kv_pair).to be_nil
    end

    it "returns the inserted value if it's new for the given key" do
      kv_pair = [1, 'b']
      bst.insert kv_pair
      expect(bst.insert [1, 'bb']).to eq 'bb'
    end
  end

  describe "#find" do
    let(:key) { 5 }
    let(:val) { 'b' }
    let(:kv_pair) { [key, val] }
    it "returns nil if the key isn't present" do
      expect(bst.find key).to be_nil
    end

    it "returns the value if the key is present" do
      bst.insert(kv_pair)
      expect(bst.find key).to eq val
    end
  end
end

