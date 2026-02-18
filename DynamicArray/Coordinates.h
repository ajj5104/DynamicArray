#pragma once
#include "DynamicArray.h"
#include <array>

template <typename T>
class Coordinates {
private:
	DynamicArray<T> x_coords;
	DynamicArray<T> y_coords;

public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	Coordinates() {}

	/// <summary>
	/// Parameterized Constructor
	/// </summary>
	/// <param name="count">The number of coordinates in the sample</param>
	Coordinates(int count) {
		x_coords.SetSize(count);
		y_coords.SetSize(count);
	}

	/// <summary>
	/// Adds a coordinate to the system using two distinct variables
	/// </summary>
	/// <param name="x">The x-coordinate</param>
	/// <param name="y">The y-coordinate</param>
	void PushBack(const T& x, const T& y) {
		if (x_coords.GetQuantity() == y_coords.GetQuantity()) {
			x_coords.PushBack(x);
			y_coords.PushBack(y);
		}
	}

	/// <summary>
	/// Adds a coordinate to the system using an array
	/// </summary>
	/// <param name="pair">Must be in format [x,y]</param>
	void PushBack(const T pair[]) {
		if (x_coords.GetQuantity() == y_coords.GetQuantity()) {
			x_coords.PushBack(pair[0]);
			y_coords.PushBack(pair[1]);
		}
	}

	/// <summary>
	/// Allows for a coordinate pair to be returned
	/// </summary>
	/// <param name="idx">The index of the coordinate pair in system</param>
	/// <returns>An array coordinate pair</returns>
	std::array<T, 2> ReturnCoordinate(int idx) {
		std::array<T, 2> coordinates = { x_coords.FindAtIndex(idx), y_coords.FindAtIndex(idx) };
		return coordinates;
	}
};