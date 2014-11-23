def quick_sort! arr, left = 0, right = arr.length - 1, &comp
  # left is greater than right when there are two
  # elems remaining and left starts at "partition + 1"
  return if left >= right 

  pivot_idx = (left + right) / 2
  # move pivot to left-most index so comparisons
  # to remaining elements are sequential
  swap! arr, pivot_idx, left

  num_smaller = 0
  pivot = arr[left]
  (left + 1..right).each do |i|
    current_el = arr[i]
    current_el_precedes = (block_given? ? comp.call(current_el, pivot)
                                        : current_el < pivot)
    if current_el_precedes
      num_smaller += 1
      swap! arr, i, left + num_smaller
    end
  end
  
  # right partition separates pivot's smaller
  # els from pivot's greater els
  right_partition = left + num_smaller
  swap! arr, left, right_partition
  quick_sort! arr, left, right_partition - 1, &comp
  quick_sort! arr, right_partition + 1, right, &comp
end

def swap! arr, i, j
  arr[i], arr[j] = arr[j], arr[i]
end

