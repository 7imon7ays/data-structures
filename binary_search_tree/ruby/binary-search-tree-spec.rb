require 'rspec'
require './binary-search-tree.rb'

describe BinarySearchTree do
  subject(:bst) { BinarySearchTree.new }
  describe "#insert" do
    it "returns nil if the insertion is redundant" do
      bst.insert a: 1
      expect(bst.insert a: 1).to be_nil
    end

    it "returns the inserted kv hash if the insertion is new" do
      kv_hash = { a: 1 }
      expect(bst.insert kv_hash).to eq kv_hash
    end
  end

  describe "#find" do
    let(:key) { :a }
    let(:kv) { { key => 1} }
    let(:value) { kv[key] }
    it "returns nil if the key isn't present" do
      expect(bst.find key).to be_nil
    end

    it "returns the value if the key is present" do
      bst.insert(kv)
      expect(bst.find key).to eq value
    end
  end
end

