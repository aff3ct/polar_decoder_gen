#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "Generator_polar_TTA_SC_sys.hpp"

using namespace aff3ct;
using namespace aff3ct::generator;

Generator_polar_TTA_SC_sys
::Generator_polar_TTA_SC_sys(const int& K,
                             const int& N,
                             const float& snr,
                             const std::vector<bool>& frozen_bits,
                             const std::vector<Pattern_polar_i*> &patterns,
                             const int idx_r0,
                             const int idx_r1,
                             std::ostream &dec_stream,
                             std::ostream &graph_stream)
: Generator_polar_TTA(K,
                      N,
                      snr,
                      frozen_bits,
                      patterns,
                      idx_r0,
                      idx_r1,
                      "Decoder_polar_TTA_SC_sys",
                      "DECODER_POLAR_TTA_SC_SYS",
                      dec_stream,
                      dec_stream,
                      graph_stream,
                      graph_stream,
                      false)
{
}

Generator_polar_TTA_SC_sys
::~Generator_polar_TTA_SC_sys()
{
}

void Generator_polar_TTA_SC_sys
::generate_class_header(const std::string   class_name,
                        const std::string   fbits_name,
                              std::ostream &stream1,
                              std::ostream &stream2)
{
	stream1        << "#include \"Decoder_simd_unrolled.h\"" << std::endl;
	stream1        <<                                           std::endl;
	stream1        << "void Decoder_simd_unrolled::decode()" << std::endl;
	stream1        << "{"                                    << std::endl;
	stream1 << tab << "char64 l_a;"                          << std::endl;
	stream1 << tab << "char64 l_b;"                          << std::endl;
	stream1 << tab << "char64 l_c;"                          << std::endl;
	stream1 << tab << "char8  temp_s;"                       << std::endl;
	stream1 << tab <<                                           std::endl;
}

void Generator_polar_TTA_SC_sys
::generate_class_footer(std::ostream &stream)
{
	stream << "};" << "" << std::endl;
}

void Generator_polar_TTA_SC_sys
::recursive_generate_decoder(const Binary_node<Pattern_polar_i>* node_curr, std::ostream &stream)
{
	n_nodes_before_compression++;

	if (!node_curr->is_leaf()) // stop condition
	{
		if (!node_curr->get_c()->apply_f().empty())
			stream << tab << node_curr->get_c()->apply_f();

		this->recursive_generate_decoder(node_curr->get_left(), stream); // recursive call

		if (!node_curr->get_c()->apply_g().empty())
			stream << tab << node_curr->get_c()->apply_g();

		this->recursive_generate_decoder(node_curr->get_right(), stream); // recursive call
	}

	if (!node_curr->get_c()->apply_h().empty())
		stream << tab << node_curr->get_c()->apply_h();
}

void Generator_polar_TTA_SC_sys
::recursive_generate_short_decoder(const Binary_node<Pattern_polar_i>* node_curr, std::ostream &stream)
{
	// TODO
}
