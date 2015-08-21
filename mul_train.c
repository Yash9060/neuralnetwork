#include "fann.h"

int main()
{
    const unsigned int num_input = 9;
    const unsigned int num_output = 20;
    const unsigned int num_layers = 2;
    const unsigned int num_neurons_hidden = 20;
    const float desired_error = (const float) 0.001;
    const unsigned int max_epochs = 10000;
    const unsigned int epochs_between_reports = 1000;

    struct fann *ann = fann_create_standard(num_layers, num_input,
        num_neurons_hidden, num_output);

    fann_set_activation_function_hidden(ann, FANN_SIGMOID);
    fann_set_activation_function_output(ann, FANN_SIGMOID);

    fann_train_on_file(ann, "fann_train_data.data", max_epochs,
        epochs_between_reports, desired_error);

    fann_save(ann, "fann_output_data.data");

    fann_destroy(ann);

    return 0;
}
