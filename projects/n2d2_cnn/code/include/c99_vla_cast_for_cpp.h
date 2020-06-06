#ifndef C99_VLA_CAST_FOR_CPP_H
#define C99_VLA_CAST_FOR_CPP_H

#define DECLARE_2D_VLA_ARRAY_AND_CAST(elements_type_t, cast_type_t, rows, cols, output_reference, input_pointer)\
	typedef elements_type_t cast_type_t[rows][cols];\
	cast_type_t &output_reference = *reinterpret_cast<cast_type_t*>(input_pointer)

#define DECLARE_3D_VLA_ARRAY_AND_CAST(elements_type_t, cast_type_t, channels, rows, cols, output_reference, input_pointer)\
	typedef elements_type_t cast_type_t[channels][rows][cols];\
	cast_type_t &output_reference = *reinterpret_cast<cast_type_t*>(input_pointer)

#define DECLARE_2D_VLA_ARRAY_OF_PTR_TO_2D_VLA_ARRAY(elements_type_t, interal_type_t, internal_rows, internal_cols, cast_type_t, ptr_rows, ptr_cols, output_reference, input_pointer)\
 	typedef elements_type_t internal_type_t[internal_rows][internal_cols];\
 	typedef internal_type_t* cast_type_t[ptr_rows][ptr_cols];\
	cast_type_t & output_reference = *reinterpret_cast<cast_type_t*>(input_pointer);

#endif
 

