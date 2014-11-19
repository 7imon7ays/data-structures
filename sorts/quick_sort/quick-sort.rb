def quick_sort! arr, left = 0, right = arr.length - 1
  return if left >= right

  pivot_idx = (left + right) / 2
  swap! arr, pivot_idx, left

  partition = left + 1
  (left + 1..right).each do |i|
    if arr[i] < arr[left]
      swap! arr, i, partition
      partition += 1
    end
  end
  partition -= 1
  swap! arr, left, partition
  quick_sort! arr, left, partition - 1
  quick_sort! arr, partition + 1, right
end

def swap! arr, i, j
  arr[i], arr[j] = arr[j], arr[i]
end

