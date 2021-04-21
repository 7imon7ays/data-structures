class Node(object):
    __slots__ = ('_val', '_left', '_right',)

    def __init__(self, val, left=None, right=None):
        self._val = val
        self._left = left
        self._right = right

    @property
    def left(self):
        return self._left

    @property
    def right(self):
        return self._right

    @property
    def val(self):
        return self._val

    def __str__(self):
        descendants = _flatten_children(self)
        strings = []
        depth = self.max_depth
        new_gen_idx = 0
        new_gen_incr = 2

        for i, node in enumerate([self] + descendants):
            strings.append('\t' * depth)
            strings.append(str(node.val))
            if i == new_gen_idx:
                strings.append('\n')
                new_gen_idx += new_gen_incr
                new_gen_incr *= 2
                depth -= 1

        return ''.join(strings)
    
    @property
    def max_depth(self):
        depth = 1
        if self.left is None and self.right is None:
            return depth
        if self.left is None:
            return depth + self.right.max_depth
        if self.right is None:
            return depth + self.left.max_depth

        return depth + max(self.left.max_depth, self.right.max_depth)

    @property
    def children(self):
        if self.left is None and self.right is None:
            return []
        if self.left is None:
            return [self.right]
        if self.right is None:
            return [self.left]

        return [self.left, self.right]

    def get_predecessor(self, val, prev=None):
        if val == self.val:
            return self.val
        if val > self.val:
            if self.right:
                return self.right.get_predecessor(val, self)
            return self.val
        if val < self.val:
            if self.left:
                return self.left.get_predecessor(val, prev)
            return prev.val if prev else None


"""
       5
     2    7
   1 3   6 8

5, 2, 7, 1, 3, 6, 8
"""


def _flatten_children(node):
    flat_nodes = []
    children = node.children
    while len(children) > 0:
        child = children.pop(0)
        flat_nodes.append(child)
        children.extend(child.children)

    return flat_nodes


def build():
    n1 = Node(1) #, Node(0.5), Node(1.5))
    # n25 = Node(2.5, Node(2.25))
    n3 = Node(3) #, n25)
    n2 = Node(2, n1, n3)

    n6 = Node(6)
    n8 = Node(8)
    n7 = Node(7, n6, n8)

    n5 = Node(5, n2, n7)

    return n5


n5 = build()
print n5.get_predecessor(2.5)
# print n5
