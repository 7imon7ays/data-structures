require "./node"

class LinkedList
  def initialize(value)
    @head = UnaryNode.new(value)
  end

  def append(value)
    this_node = @head

    while this_node.next
      this_node = this_node.next
    end
    this_node.next = UnaryNode.new(value)
    this_node.next.value
  end

  def interpolate(value, desired_parent_value)
    parent_node = @head

    until parent_node.value == desired_parent_value
      parent_node = parent_node.next
      throw "Could not find desired parent value." if parent_node.nil?
    end

    new_node, new_node_child = UnaryNode.new(value), parent_node.next
    new_node.next, parent_node.next = new_node_child, new_node
    new_node.value
  end

  def include?(value)
    this_node = @head

    while true
      return true if this_node.value == value
      if this_node.next then this_node = this_node.next else break end
    end
    false
  end
end
