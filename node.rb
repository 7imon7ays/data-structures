class UnaryNode
  attr_accessor :value, :next
  
  def initialize(value = nil)
    @value = value
    @next = nil
  end
end

class BinaryNode
  attr_accessor :value, :left_child, :right_child
  
  def inititalize(value = nil)
    @value = value
    @left_child = nil
    @right_child = nil
  end
end

class AryNode
  attr_reader :value, :children
  
  def inititalize(value = nil)
    @value = value
    @children = []
  end
end
