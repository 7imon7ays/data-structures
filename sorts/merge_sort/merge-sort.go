package main

import (
	"bufio"
	"fmt"
	"os"
)

type comp func(int, int) bool

func sort(nums []int, getComp comp) []int {
	if len(nums) < 2 {
		return nums
	}

	mid := len(nums) / 2
	left := nums[:mid]
	right := nums[mid:]

	left = sort(left, getComp)
	right = sort(right, getComp)

	return merge(left, right, getComp)
}

func merge(left, right []int, getComp comp) []int {
	length := len(left) + len(right)
	merged := make([]int, 0, length)

	l := 0
	r := 0
	var n int

	for l < len(left) && r < len(right) {
		if getComp(left[l], right[r]) {
			n = left[l]
			l++
		} else {
			n = right[r]
			r++
		}
		merged = append(merged, n)
	}

	for ; l < len(left); l++ {
		merged = append(merged, left[l])
	}

	for ; r < len(right); r++ {
		merged = append(merged, right[r])
	}

	return merged
}

func main() {
	nums := []int{8, 3, 7, 4, 0, 2, 7, 6, 1}
	sorted := sort(nums, getComp)

	fmt.Print("Sorted:")
	fmt.Printf("%v\n", sorted)
}

func getComp(a, b int) bool {
	reader := bufio.NewReader(os.Stdin)
	fmt.Printf("Is %d less than %d?\n", a, b)
	ans, _ := reader.ReadString('\n')
	return ans == "y\n"
}
