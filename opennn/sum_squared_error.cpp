//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   S U M   S Q U A R E D   E R R O R   C L A S S                         
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "sum_squared_error.h"

namespace OpenNN
{

/// Default constructor. 
/// It creates a sum squared error term not associated to any neural network and not measured on any data set.
/// It also initializes all the rest of class members to their default values.

SumSquaredError::SumSquaredError() : LossIndex()
{
}


/// Neural network constructor. 
/// It creates a sum squared error term associated to a neural network but not measured on any data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.

SumSquaredError::SumSquaredError(NeuralNetwork* new_neural_network_pointer) 
: LossIndex(new_neural_network_pointer)
{
}


/// Data set constructor. 
/// It creates a sum squared error not associated to any neural network but to be measured on a data set object.
/// It also initializes all the rest of class members to their default values.
/// @param new_data_set_pointer Pointer to a data set object.

SumSquaredError::SumSquaredError(DataSet* new_data_set_pointer)
: LossIndex(new_data_set_pointer)
{
}


/// Neural network and data set constructor. 
/// It creates a sum squared error associated to a neural network and measured on a data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.

SumSquaredError::SumSquaredError(NeuralNetwork* new_neural_network_pointer, DataSet* new_data_set_pointer)
 : LossIndex(new_neural_network_pointer, new_data_set_pointer)
{
}


/// XML constructor. 
/// It creates a sum squared error not associated to any neural network and not measured on any data set.
/// It also sets all the rest of class members from a TinyXML document.
/// @param sum_squared_error_document XML document with the class members.

SumSquaredError::SumSquaredError(const tinyxml2::XMLDocument& sum_squared_error_document)
 : LossIndex(sum_squared_error_document)
{
    from_XML(sum_squared_error_document);
}


/// Copy constructor. 
/// It creates a sum squared error not associated to any neural network and not measured on any data set.
/// It also sets all the rest of class members from another sum squared error object.
/// @param new_sum_squared_error Object to be copied. 

SumSquaredError::SumSquaredError(const SumSquaredError& new_sum_squared_error)
 : LossIndex(new_sum_squared_error)
{

}


/// Destructor.

SumSquaredError::~SumSquaredError() 
{
}


/// This method calculates the sum squared error of the given batch.
/// Returns the sum squared error of this batch.
/// @param batch_indices Indices of the batch instances corresponding to the dataset

type SumSquaredError::calculate_batch_error(const Tensor<Index, 1>& batch_indices) const
{
#ifdef __OPENNN_DEBUG__

check();

#endif

    // Data set

    const Tensor<type, 2> inputs = data_set_pointer->get_input_data(batch_indices);

    const Tensor<type, 2> targets = data_set_pointer->get_target_data(batch_indices);

    const Tensor<type, 2> outputs = neural_network_pointer->calculate_trainable_outputs(inputs);

    return sum_squared_error(outputs, targets);
}


type SumSquaredError::calculate_batch_error(const Tensor<Index, 1>& batch_indices, const Tensor<type, 1>& parameters) const
{
#ifdef __OPENNN_DEBUG__

check();

#endif

    // Data set

    const Tensor<type, 2> inputs = data_set_pointer->get_input_data(batch_indices);

    const Tensor<type, 2> targets = data_set_pointer->get_target_data(batch_indices);

    const Tensor<type, 2> outputs = neural_network_pointer->calculate_trainable_outputs(inputs, parameters);

    return sum_squared_error(outputs, targets);
}


/// Calculates the squared error terms for each instance, and returns it in a vector of size the number training instances. 

Tensor<type, 1> SumSquaredError::calculate_training_error_terms(const Tensor<type, 2>& outputs, const Tensor<type, 2>& targets) const
{
    #ifdef __OPENNN_DEBUG__

    check();

    #endif
/*
    return error_rows(outputs, targets);
*/
    return Tensor<type, 1>();
}


/// Calculates the squared error terms for each instance, and returns it in a vector of size the number training instances.
/// @param parameters

Tensor<type, 1> SumSquaredError::calculate_training_error_terms(const Tensor<type, 1>& parameters) const
{
    #ifdef __OPENNN_DEBUG__

    check();

    #endif
/*
    const Tensor<type, 2> inputs = data_set_pointer->get_training_input_data();

    const Tensor<type, 2> targets = data_set_pointer->get_training_target_data();

    const Tensor<type, 2> outputs = neural_network_pointer->calculate_trainable_outputs(inputs, parameters);

    return error_rows(outputs, targets);
*/
    return Tensor<type, 1>();

}


/// Returns the squared errors of the training instances. 
/// @todo Use batchs, ready to review.

Tensor<type, 1> SumSquaredError::calculate_squared_errors() const
{
   #ifdef __OPENNN_DEBUG__

   check();

   #endif
/*
    bool is_forecasting = false;

    if(neural_network_pointer->has_long_short_term_memory_layer() || neural_network_pointer->has_recurrent_layer()) is_forecasting = true;

   // Data set

   const Tensor<Tensor<Index, 1>, 1> batch_indices = data_set_pointer->get_training_batches(!is_forecasting);

   const Index batches_number = batch_indices.size();

   // Loss index

   Tensor<type, 1> squared_errors(batches_number);

    #pragma omp parallel for

   for(Index i = 0; i < batches_number ; i++)
   {
      // Input vector

      const Tensor<type, 2> inputs = data_set_pointer->get_input_data(batch_indices[i]);

      // Output vector

      const Tensor<type, 2> outputs = neural_network_pointer->calculate_trainable_outputs(inputs);

      // Target vector

      const Tensor<type, 2> targets = data_set_pointer->get_target_data(batch_indices[i]);

      // Error

      squared_errors[i] = sum_squared_error(outputs, targets);
   }

   return squared_errors;
*/
   return Tensor<type, 1>();

}


/// This method calculates the second order loss.
/// It is used for optimization of parameters during training.
/// Returns a second order terms loss structure, which contains the values and the Hessian of the error terms function.

LossIndex::SecondOrderLoss SumSquaredError::calculate_terms_second_order_loss() const
{
#ifdef __OPENNN_DEBUG__

check();

#endif
/*
    // Neural network

    const Index layers_number = neural_network_pointer->get_trainable_layers_number();

    const Index parameters_number = neural_network_pointer->get_parameters_number();

     bool is_forecasting = false;

    if(neural_network_pointer->has_long_short_term_memory_layer() || neural_network_pointer->has_recurrent_layer()) is_forecasting = true;

    // Data set

    const Tensor<Tensor<Index, 1>, 1> training_batches = data_set_pointer->get_training_batches(!is_forecasting);

    const Index batches_number = training_batches.size();

    SecondOrderLoss terms_second_order_loss(parameters_number);

     #pragma omp parallel for

    for(Index i = 0; i < batches_number; i++)
    {
        const Tensor<type, 2> inputs = data_set_pointer->get_input_data(training_batches.chip(i,0));
        const Tensor<type, 2> targets = data_set_pointer->get_target_data(training_batches.chip(i,0));

        const Tensor<Layer::ForwardPropagation, 1> forward_propagation = neural_network_pointer->calculate_forward_propagation(inputs);

        const Tensor<type, 1> error_terms
                = calculate_training_error_terms(forward_propagation[layers_number-1].activations, targets);

        const Tensor<type, 2> output_gradient = (forward_propagation[layers_number-1].activations - targets).divide(error_terms, 0);

        const Tensor<Tensor<type, 2>, 1> layers_delta = calculate_layers_delta(forward_propagation, output_gradient);

        const Tensor<type, 2> error_terms_Jacobian
                = calculate_error_terms_Jacobian(inputs, forward_propagation, layers_delta);

        const Tensor<type, 2> error_terms_Jacobian_transpose = error_terms_Jacobian.calculate_transpose();

        const type loss = dot(error_terms, error_terms);

        const Tensor<type, 1> gradient = dot(error_terms_Jacobian_transpose, error_terms);

        Tensor<type, 2> hessian_approximation;
        //hessian_approximation.dot(error_terms_Jacobian_transpose, error_terms_Jacobian);

          #pragma omp critical
        {
            terms_second_order_loss.loss += loss;
            terms_second_order_loss.gradient += gradient;
            terms_second_order_loss.hessian += hessian_approximation;
         }
    }

    const Tensor<type, 2> regularization_hessian = calculate_regularization_hessian();

    terms_second_order_loss.gradient *= 2.0;
    terms_second_order_loss.hessian *= 2.0;

    return terms_second_order_loss;
*/
    return LossIndex::SecondOrderLoss();
}


/// Returns a string with the name of the sum squared error loss type, "SUM_SQUARED_ERROR".

string SumSquaredError::get_error_type() const
{
   return "SUM_SQUARED_ERROR";
}


/// Returns a string with the name of the sum squared error loss type in text format.

string SumSquaredError::get_error_type_text() const
{
   return "Sum squared error";
}


/// Returns a representation of the sum squared error object, in XML format. 

tinyxml2::XMLDocument* SumSquaredError::to_XML() const
{
   ostringstream buffer;

   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   // Sum squared error

   tinyxml2::XMLElement* root_element = document->NewElement("SumSquaredError");

   document->InsertFirstChild(root_element);

   // Display

//   {
//      tinyxml2::XMLElement* display_element = document->NewElement("Display");
//      root_element->LinkEndChild(display_element);

//      buffer.str("");
//      buffer << display;

//      tinyxml2::XMLText* display_text = document->NewText(buffer.str().c_str());
//      display_element->LinkEndChild(display_text);
//   }

   return document;
}


// void write_XML(tinyxml2::XMLPrinter&) const method

/// Serializes the cross entropy error object into a XML document of the TinyXML library without keep the DOM tree in memory.
/// See the OpenNN manual for more information about the format of this document

void SumSquaredError::write_XML(tinyxml2::XMLPrinter& file_stream) const
{
    // Error type

    file_stream.OpenElement("Error");

    file_stream.PushAttribute("Type", "SUM_SQUARED_ERROR");

    file_stream.CloseElement();

    // Regularization

    write_regularization_XML(file_stream);
}


/// Loads a sum squared error object from a XML document.
/// @param document TinyXML document containing the members of the object.

void SumSquaredError::from_XML(const tinyxml2::XMLDocument& document)
{
    const tinyxml2::XMLElement* root_element = document.FirstChildElement("SumSquaredError");

    if(!root_element)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: SumSquaredError class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Sum squared element is nullptr.\n";

        throw logic_error(buffer.str());
    }

    // Regularization

    tinyxml2::XMLDocument regularization_document;
    tinyxml2::XMLNode* element_clone;

    const tinyxml2::XMLElement* regularization_element = root_element->FirstChildElement("Regularization");

    element_clone = regularization_element->DeepClone(&regularization_document);

    regularization_document.InsertFirstChild(element_clone);

    regularization_from_XML(regularization_document);
}


type SumSquaredError::sum_squared_error(const Tensor<type, 2>& outputs ,const Tensor<type, 2>& targets) const
{
    const auto error = targets - outputs;

    const Eigen::array<IndexPair<Index>, 2> product_dimensions = { IndexPair<Index>(0, 0), IndexPair<Index>(1, 1) };

    const Tensor<type, 0> sse = error.contract(error, product_dimensions);

    return sse(0);
}
}

// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2020 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
