# This is wrong.
def max_load(cake_tuples, capacity):
    prev_loads = []

    for current_capacity in range(capacity + 1):
        best_solo_cake = (0, 0,)
        best_cake_with_prev = (0, 0,)

        for cake_weight, cake_value in cake_tuples:
            # Best one-off value.
            if cake_weight <= current_capacity:
                if best_solo_cake[1] < cake_value:
                    best_solo_cake = (cake_weight, cake_value,)

            # Best cumulative value.
            for prev_load in prev_loads:
                if prev_load[0] + cake_weight <= current_capacity:
                    if best_cake_with_prev[1] <= cake_value:
                        best_cake_with_prev = (cake_weight, cake_value,)

        if best_solo_cake[1] >= best_cake_with_prev[1]:
            winner = best_solo_cake
        else:
            winner = (
                prev_load[0] + best_cake_with_prev[0],
                prev_load[1] + best_cake_with_prev[1],
            )
        prev_loads.append(winner)

    print prev_loads
    return prev_loads[-1][1]


cake_tuples = [(7, 160), (3, 90), (2, 15)]
capacity = 20
result = max_load(cake_tuples, capacity) 
assert result == 555, '%s is not equal to 555' % result
