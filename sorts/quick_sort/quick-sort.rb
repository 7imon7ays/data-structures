def quick_sort! arr, left = 0, right = arr.length - 1
  # left is greater than right when there are two
  # els remaining and left starts at "partition + 1"
  return if left >= right 

  pivot_idx = (left + right) / 2
  # move pivot to left-most index so comparisons
  # to remaing elements are sequential
  swap! arr, pivot_idx, left

  num_smaller = 0
  (left + 1..right).each do |i|
    if arr[i] < arr[left]
      num_smaller += 1
      swap! arr, i, left + num_smaller
    end
  end
  
  # right partition separates pivot's smaller
  # els from pivot's greater els
  right_partition = left + num_smaller
  swap! arr, left, right_partition
  quick_sort! arr, left, right_partition - 1
  quick_sort! arr, right_partition + 1, right
end

def swap! arr, i, j
  arr[i], arr[j] = arr[j], arr[i]
end

