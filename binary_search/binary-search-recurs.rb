def binary_search arr, val, left = 0, right = arr.length - 1
  mid_i = (left + right) / 2

  case arr[mid_i] <=> val
  when 0
    mid_i
  when 1
    return nil if left == mid_i - 1 && arr[left] != val
    binary_search arr, val, left, mid_i - 1
  when -1
    binary_search arr, val, mid_i + 1, right
  end
end

