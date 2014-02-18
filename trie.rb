class Trie
  def initialize
    @root = Hash.new
  end

  def build(expression, value)
    node = @root
    sub_expression = format(expression)

    sub_expression.each_char do |ch|
      node[ch] ||= Hash.new
      node = node[ch]
    end
    node[:leaf] = { sub_expression => value }
  end

  def find(expression)
    node = @root
    sub_expression = format(expression)

    sub_expression.each_char do |ch|
      return nil unless node = node[ch]
    end
    node[:leaf][sub_expression]
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
