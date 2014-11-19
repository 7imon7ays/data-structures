class Trie
  def initialize
    @root = Hash.new
  end

  def add(expression)
    node = @root
    sub_expression = format(expression)

    sub_expression.each_char do |ch|
      node[ch] ||= Hash.new
      node = node[ch]
    end
    node[:leaf] = expression
  end

  def find(expression)
    node = @root
    sub_expression = format(expression)

    sub_expression.each_char do |ch|
      return nil unless node = node[ch]
    end
    node[:leaf]
  end

  private

  def format(string)
    articles_filter = /\A(the\s|a\s)/i
    string
      .gsub(articles_filter, "")
      .gsub(" ", "")
      .downcase
  end
end

