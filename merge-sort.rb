def merge_sort(array)
  return array if array.count < 2

  middle = array.length / 2
  left, right = array[0...middle], array[middle..-1]
  sorted_left, sorted_right = merge_sort(left), merge_sort(right)
  merge(sorted_left, sorted_right)
end

def merge(left, right)
  sorted_array = []
  while first_left = left.shift
    while right.first && first_left > right.first
      sorted_array << right.shift
    end
    sorted_array << first_left
  end
  sorted_array.concat right
end

