import argparse
import random

def generate_random_array(array_size, number_range):
    """
    Generate a random array with the given size and range.
    
    Args:
        array_size (int): The number of elements in the array.
        number_range (tuple): A tuple (min, max) defining the range of numbers for the array.
        
    Returns:
        str: A formatted string representing a C++ array.
        
    Raises:
        ValueError: If the minimum value in the range is greater than the maximum value.
    """
    min_val, max_val = number_range

    if min_val > max_val:
        raise ValueError("Invalid range: min should be less than or equal to max.")

    random_array = [random.randint(min_val, max_val) for _ in range(array_size)]

    # Format as a C++ array
    cpp_array = "{ " + ", ".join(map(str, random_array)) + " };"
    return f"int arr[{array_size}] = {cpp_array}"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a random array to hardcode in C++")
    parser.add_argument(
        "-s", "--array-size",
        type=int,
        default=100,
        help="The size of the array (number of elements)."
    )
    parser.add_argument(
        "-l", "--min-value",
        type=int,
        default=-300,
        help="The minimum value of the number range."
    )
    parser.add_argument(
        "-u", "--max-value",
        type=int,
        default=300,
        help="The maximum value of the number range."
    )
    args = parser.parse_args()

    try:
        cpp_array_output = generate_random_array(args.array_size, (args.min_value, args.max_value))
        print(cpp_array_output)
    except ValueError as e:
        print(f"Error: {e}")
