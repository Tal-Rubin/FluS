/**
 * @file dynamic_variable.h
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief A state data structure
 * @version 0.1
 * @date 2021-11-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FLUS_DY_VAR_H_
#define FLUS_DY_VAR_H_

#include <valarray>
#include <array>
#include <cstddef>

class Dynamic_Variable {
  public:
  /**
   * @brief Construct a new Dynamic_Variable object
   * 
   * @param num_ele Number of elements / finite volume data 
   * @param num_fields Number of fields in each element ( = number of equations)
   * @param num_coeff Number of parameters used to describe each field ( = 1 for finite volume, more for discontinuous Galerkin)
   */
  Dynamic_Variable(std::size_t num_ele, std::size_t num_fields, std::size_t num_coeff);

  /**
   * @brief Construct a new finite volume Dynamic_Variable object
   * 
   * @param num_ele Number of elements / finite volume data.
   * @param num_fields Number of fields in each element ( = number of equations).
   * 
   * Assumes one parameter per field.
   */
  Dynamic_Variable(std::size_t num_ele, std::size_t num_fields);

  /**
   * @brief Construct a new Dynamic_Variable object
   * 
   * @param dim Array containing {Number of elements, Number of fields, Number of parameters}.
   */
  Dynamic_Variable(std::array<std::size_t, 3> dim);

  /**
   * @brief Access an element (non-iterable, read / write)
   * 
   * @param ele_number Element number to be accessed.
   * @return std::slice_array<double> Element data.
   */
  inline std::slice_array<double> element (std::size_t ele_number) { 
    return data_[std::slice(ele_number * element_size_, element_size_, 1)];
  };

  /**
   * @brief Get a (read only) iterable element data
   * 
   * @param ele_number Element number to be read.
   * @return std::valarray<double> Element data.
   */
  inline std::valarray<double> get_element (std::size_t ele_number) const {
    return data_[std::slice(ele_number * element_size_, element_size_, 1)];
  };
  
  /**
   * @brief Access a field parameter (non-iterable, read / write)
   * 
   * @param field_number Field number (counting starts at 0).
   * @param coeff_number Parameter number (counting starts at 0).
   * @return std::slice_array<double> Field parameter data for the entire mesh.
   */
  inline std::slice_array<double> field_coeff (std::size_t field_number, std::size_t coeff_number) { 
    return data_[std::slice(field_number * dim_[2] + coeff_number, dim_[0], element_size_)];
  };

  /**
   * @brief Get a (read only) iterable field parameter data
   * 
   * @param field_number Field number (counting starts at 0).
   * @param coeff_number Parameter number (counting starts at 0).
   * @return std::valarray<double> Field parameter data for the entire mesh.
   */
  inline std::valarray<double> get_field_coeff (std::size_t field_number, std::size_t coeff_number) const {
    return data_[std::slice(field_number * dim_[2] + coeff_number, dim_[0], element_size_)];
  } ;

  /// Getter funciton for the dim_ array
  std::array<std::size_t, 3> dim() const;
  /// Getter funciton for the element size
  std::size_t element_size() const;
  /// Getter funciton for number of coefficinets
  std::size_t coeff_num() const;

  /// The dynamic variable data
  std::valarray<double> data_;

  private:
  /// Array containing the division of the raw data to elements, fields and parameters
  std::array<std::size_t, 3> dim_;
  /// The number of parameters in each element (# fields * # parameters per field)
  std::size_t element_size_;
}; 

#endif  // FLUS_DY_VAR_H_