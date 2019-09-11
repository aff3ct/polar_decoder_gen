#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "Generator_polar_GPP_SCL_sys.hpp"

using namespace aff3ct;
using namespace aff3ct::generator;

Generator_polar_GPP_SCL_sys
::Generator_polar_GPP_SCL_sys(const int& K,
                              const int& N,
                              const float& snr,
                              const std::vector<bool>& frozen_bits,
                              const std::vector<Pattern_polar_i*> &patterns,
                              const int idx_r0,
                              const int idx_r1,
                              std::ostream &dec_stream,
                              std::ostream &graph_stream)
: Generator_polar_GPP(K,
                      N,
                      snr,
                      frozen_bits,
                      patterns,
                      idx_r0,
                      idx_r1,
                      "Decoder_polar_SCL_fast_CA_sys",
                      "DECODER_POLAR_SCL_FAST_SYS_CA",
                      dec_stream,
                      dec_stream,
                      graph_stream,
                      graph_stream,
                      false)
{
}

Generator_polar_GPP_SCL_sys
::~Generator_polar_GPP_SCL_sys()
{
}

void Generator_polar_GPP_SCL_sys
::generate_class_header(const std::string   class_name,
                        const std::string   fbits_name,
                              std::ostream &stream1,
                              std::ostream &stream2)
{
	stream1 << "template <typename B, typename R, class API_polar>"                                       << std::endl;
	stream1 << "class " << class_name << " : public " << this->mother_class_name << "<B, R, API_polar>"   << std::endl;
	stream1 << "{"                                                                                        << std::endl;
	stream1 << "public:"                                                                                  << std::endl;
	stream1 << tab << class_name << "(const int& K, const int& N, const int& L, CRC<B>& crc,"
	               <<               " const int n_frames = 1)"                                            << std::endl;
	stream1 << tab << ": Decoder(K, N, n_frames, API_polar::get_n_frames()),"                             << std::endl;
	stream1 << tab << "  " << this->mother_class_name << "<B, R, API_polar>(K, N, L, " << this->fbits_name
	               << ", crc)"                                                                            << std::endl;
	stream1 << tab << "{"                                                                                 << std::endl;
	stream1 << tab << tab << "const std::string name = \"" + class_name + "\";"                           << std::endl;
	stream1 << tab << tab << "this->set_name(name);"                                                      << std::endl;
	stream1 << tab << tab << "assert(N == " << N << ");"                                                  << std::endl;
	stream1 << tab << tab << "assert(K == " << K << ");"                                                  << std::endl;
	stream1 << tab << "}"                                                                                 << std::endl;
	stream1                                                                                               << std::endl;
	stream1 << tab << "virtual ~" << class_name << "()"                                                   << std::endl;
	stream1 << tab << "{"                                                                                 << std::endl;
	stream1 << tab << "}"                                                                                 << std::endl;
	stream1                                                                                               << std::endl;

	stream2 << tab << "void _decode(const R *Y_N)"                                                        << std::endl;
	stream2 << tab << "{"                                                                                 << std::endl;
	stream2 << tab << tab << "using namespace tools;"                                                     << std::endl;
	stream2                                                                                               << std::endl;
	stream2 << tab << tab << "auto  y = Y_N;"                                                             << std::endl;
	stream2 << tab << tab << "auto &l = this->l;"                                                         << std::endl;
	stream2 << tab << tab << "auto &s = this->s;"                                                         << std::endl;
	stream2                                                                                               << std::endl;
}

void Generator_polar_GPP_SCL_sys
::generate_class_footer(std::ostream &stream)
{
	stream << tab << "}" << std::endl;
	stream << "};" << "" << std::endl;
}

void Generator_polar_GPP_SCL_sys
::recursive_generate_decoder(const Binary_node<Pattern_polar_i>* node_curr, std::ostream &stream)
{
	n_nodes_before_compression++;

	if (!node_curr->is_leaf()) // stop condition
	{
		if (!node_curr->get_c()->apply_f().empty())
			stream << node_curr->get_c()->apply_f(tab + tab);

		this->recursive_generate_decoder(node_curr->get_left(), stream); // recursive call

		if (!node_curr->get_c()->apply_g().empty())
			stream << node_curr->get_c()->apply_g(tab + tab);

		this->recursive_generate_decoder(node_curr->get_right(), stream); // recursive call
	}

	if (!node_curr->get_c()->apply_h().empty())
		stream << node_curr->get_c()->apply_h(tab + tab);
}

void Generator_polar_GPP_SCL_sys
::recursive_generate_short_decoder(const Binary_node<Pattern_polar_i>* node_curr, std::ostream &stream)
{
	// TODO
}
