Node = Struct.new :key, :val, :left, :right do
  def to_s
    "{ #{ key } => #{ val } }"
  end
end

class BinarySearchTree
  def initialize root_kv
    @root = Node.new *root_kv
  end

  def find key
    search @root, key
  end

  def insert kv_pair
    key, val = kv_pair
    search root, key, val
  end

  private

  attr_reader :root

  def search curr_node, key, val = nil
    # A nil value means this is an insertion.
    # Setting a key's value to nil is not supported.
    is_insertion = !val.nil?

    if curr_node.key == key
      # Return the val if it changed, otherwise nil.
      # Return the node's value if this is a lookup.
      is_insertion ? (curr_node.val == val ? nil : val) : curr_node.val
    elsif curr_node.key > key
      handle_subtree curr_node, 'left', key, val
    elsif curr_node.key < key
      handle_subtree curr_node, 'right', key, val
    end
  end

  def handle_subtree curr_node, side, key, val
    is_insertion = !val.nil?

    if curr_node.send(side).nil?
      # Reached a leaf. Append the child if inserting, otherwise return nil.
      is_insertion ? curr_node.send(side + '=', Node.new(key, val)) : nil
    else
      search curr_node.send(side), key, val
    end
  end
end

