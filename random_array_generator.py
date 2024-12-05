import argparse
import random

def generate_random_array(array_size, number_range, data_type, precision, sorting):
    """
    Generate a random array with the given size, range, data type, and sorting order.
    
    Args:
        array_size (int): The number of elements in the array.
        number_range (tuple): A tuple (min, max) defining the range of numbers for the array.
        data_type (str): The type of numbers to generate ('int' or 'double').
        precision (int): The number of decimal places for double types.
        sorting (str): The sorting order ('none', 'sorted', 'reverse').
        
    Returns:
        str: A formatted string representing a C++ array.
        
    Raises:
        ValueError: If the minimum value in the range is greater than the maximum value.
    """
    min_val, max_val = number_range

    if min_val > max_val:
        raise ValueError("Invalid range: min should be less than or equal to max.")

    # Generate random array based on the data type
    if data_type == "int":
        random_array = [random.randint(min_val, max_val) for _ in range(array_size)]
    elif data_type == "double":
        random_array = [round(random.uniform(min_val, max_val), precision) for _ in range(array_size)]
    else:
        raise ValueError(f"Unsupported data type: {data_type}")

    # Apply sorting
    if sorting == "sorted":
        random_array.sort()
    elif sorting == "reverse":
        random_array.sort(reverse=True)

    # Format as a C++ array
    cpp_array = "{ " + ", ".join(map(str, random_array)) + " };"
    return f"{data_type} arr[{array_size}] = {cpp_array}"


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
        type=float,
        default=-300.0,
        help="The minimum value of the number range."
    )
    parser.add_argument(
        "-u", "--max-value",
        type=float,
        default=300.0,
        help="The maximum value of the number range."
    )
    parser.add_argument(
        "-t", "--type",
        choices=["int", "double"],
        default="int",
        help="The type of numbers to generate (int, float, double). Default is int."
    )
    parser.add_argument(
        "-p", "--precision",
        type=int,
        default=2,
        help="The number of decimal places for double types. Default is 2."
    )
    parser.add_argument(
        "-o", "--order",
        choices=["none", "sorted", "reverse"],
        default="none",
        help="The order of the array (none, sorted, reverse). Default is none."
    )
    args = parser.parse_args()

    try:
        cpp_array_output = generate_random_array(
            args.array_size,
            (args.min_value, args.max_value),
            args.type,
            args.precision,
            args.order
        )
        print(cpp_array_output)
    except ValueError as e:
        print(f"Error: {e}")
