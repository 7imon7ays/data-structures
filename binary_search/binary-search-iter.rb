def binary_search arr, val
  left, right = 0, arr.length - 1

  while left <= right
    mid = (left + right) / 2
    case arr[mid] <=> val
    when 0
      return mid
    when -1
      left = mid + 1
    when 1
      right = mid - 1
    end
  end
  nil
end

