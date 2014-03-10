load 'trie.rb'
require 'rspec'

describe "trie" do
  before(:each) do
    @trie = Trie.new
  end

  it "doesn't find unstored words" do
    @trie.find("bar").should be_nil
  end

  it "finds stored words" do
    foo = "foo"
    @trie.add(foo)
    @trie.find(foo).should == foo
  end

  it "is not case sensitive" do
    crazy_case = "FoO"
    @trie.add(crazy_case)
    @trie.find(crazy_case.downcase).should == crazy_case
  end

  it "ignores articles" do
    without_article = "foo"
    with_article = "the " + without_article
    @trie.add(with_article)
    @trie.find("foo").should == with_article
  end
end

