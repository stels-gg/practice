from math import sqrt, sin  # Use the complex sqrt as we may generate complex numbers

def func(x):
    return (x ** 2) - sin(x)

def muller(x0, x1, x2, decimal_places, maximum_iterations):

    iteration_counter = 0
    iterates = [x0, x1, x2]
    solution_found = False

    while not solution_found and iteration_counter < maximum_iterations:
        final_index = len(iterates)-1
        
        h0 = iterates[final_index - 1] - iterates[final_index - 2]
        h1 = iterates[final_index] - iterates[final_index - 1]

        f_x0 = func(iterates[final_index - 2])
        f_x1 = func(iterates[final_index - 1])
        f_x2 = func(iterates[final_index])

        delta0 = (f_x1 - f_x0) / h0
        delta1 = (f_x2 - f_x1) / h1

        coeff_a = (delta1 - delta0) / (h1 + h0)
        coeff_b = coeff_a*h1 + delta1
        coeff_c = f_x2

        sqrt_delta = sqrt(pow(coeff_b,2) - 4*coeff_a*coeff_c)
        denominators = [coeff_b - sqrt_delta, coeff_b + sqrt_delta]

        # Take the higher-magnitude denominator
        next_iterate = iterates[final_index] - (2 * coeff_c)/max(denominators, key=abs)

        iterates.append(next_iterate)
        solution_found = abs(func(next_iterate)) < pow(10, -decimal_places)

        iteration_counter = iteration_counter + 1
    
    if solution_found:
        print("Solution found: {}".format(next_iterate))
    else:
        print("No solution found.")

muller(0.5, 0.7, 0.9, 20, 100)