#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

// AFF3CT header
#include <aff3ct.hpp>

#include "Generator/Polar/GPP/SC/Generator_polar_GPP_SC_sys.hpp"
#include "Generator/Polar/GPP/SCL/Generator_polar_GPP_SCL_sys.hpp"
#include "Generator/Polar/TTA/SC/Generator_polar_TTA_SC_sys.hpp"
#include "Generator/Polar/TTA/SCAN/Generator_polar_TTA_SCAN_sys.hpp"

#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_r0_left.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_r1.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_rep_left.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_spc.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_rep.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_r0.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_std.hpp"

#include "Tools/Code/Polar/Patterns/TTA/SC/Pattern_polar_TTA_SC_r0_left.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SC/Pattern_polar_TTA_SC_r1.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SC/Pattern_polar_TTA_SC_rep_left.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SC/Pattern_polar_TTA_SC_spc.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SC/Pattern_polar_TTA_SC_rep.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SC/Pattern_polar_TTA_SC_r0.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SC/Pattern_polar_TTA_SC_std.hpp"

#include "Tools/Code/Polar/Patterns/TTA/SCAN/Pattern_polar_TTA_SCAN_r0_left.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SCAN/Pattern_polar_TTA_SCAN_r1.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SCAN/Pattern_polar_TTA_SCAN_rep_left.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SCAN/Pattern_polar_TTA_SCAN_spc.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SCAN/Pattern_polar_TTA_SCAN_rep.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SCAN/Pattern_polar_TTA_SCAN_r0.hpp"
#include "Tools/Code/Polar/Patterns/TTA/SCAN/Pattern_polar_TTA_SCAN_std.hpp"

#include "Tools/Code/Polar/Patterns/TTA/Pattern_polar_tile.hpp"
#include "Tools/Code/Polar/Patterns/TTA/Pattern_polar_tile_scan.hpp"

#include "Tools/Code/Polar/Patterns/SCL/Pattern_polar_SCL_spc.hpp"
#include "Tools/Code/Polar/Patterns/SCL/Pattern_polar_SCL_r1.hpp"
#include "Tools/Code/Polar/Patterns/SCL/Pattern_polar_SCL_rep.hpp"
#include "Tools/Code/Polar/Patterns/SCL/Pattern_polar_SCL_r0.hpp"
#include "Tools/Code/Polar/Patterns/SCL/Pattern_polar_SCL_rep_left.hpp"
#include "Tools/Code/Polar/Patterns/SCL/Pattern_polar_SCL_r0_left.hpp"
#include "Tools/Code/Polar/Patterns/SCL/Pattern_polar_SCL_std.hpp"

using namespace aff3ct;

int main(int argc, char** argv)
{
	// ----------------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------ parameters management
	// ----------------------------------------------------------------------------------------------------------------

	float ebn0 = 0.f;
	std::string base_path = ".";
	std::string arch = "GPP";

	tools::Arguments_reader ar(argc, (const char**)argv);

	factory::arg_map req_args, opt_args;
	std::map<std::string, factory::header_list> headers;

	opt_args[{"help", "h"}] = {"", "print this help."};

	factory::Frozenbits_generator::parameters params_fbg;
	factory::Decoder_polar       ::parameters params_dec;
	
	factory::arg_grp arg_group;
	arg_group.push_back({params_fbg.get_prefix(), params_fbg.get_short_name() + " parameters"});
	arg_group.push_back({params_dec.get_prefix(), params_dec.get_short_name() + " parameters"});

	params_fbg.get_description(req_args, opt_args);
	params_dec.get_description(req_args, opt_args);

	req_args[{"fbg-snr" }] = {"float", "SNR for the frozen bits generation (Eb/N0 in dB, supposes a BPSK modulation)."};
	opt_args[{"dec-path"}] = {"string", "Base path where the decoder will be generated (default = current dir)."};

	opt_args[{"arch-type", "a"}] = {"string", "Target architecture.", "GPP, TTA"};

	opt_args.erase({"fbg-sigma"           });
	req_args.erase({"dec-cw-size",     "N"});
	req_args.erase({"dec-info-bits",   "K"});
	opt_args.erase({"dec-fra",         "F"});
	opt_args.erase({"dec-implem"          });
	opt_args.erase({"dec-lists",       "L"});
	opt_args.erase({"dec-no-sys"          });
	opt_args.erase({"dec-partial-adaptive"});
	opt_args.erase({"dec-simd"            });

	opt_args[{"dec-type", "D"}][2] = "SC, SCL, SCAN";

	bool need_help = false;
	if (ar.parse_arguments(req_args, opt_args))
	{
		params_fbg.store(ar.get_args());
		params_dec.K    = params_fbg.K;
		params_dec.N_cw = params_fbg.N_cw;
		params_dec.store(ar.get_args());
		if (ar.exist_arg({"arch-type", "a"}))
			arch = ar.get_arg({"arch-type", "a"});
		ebn0 = ar.get_arg_float({"fbg-snr"});
		auto esn0 = tools::ebn0_to_esn0(ebn0, params_dec.R, 1);
		params_fbg.sigma = tools::esn0_to_sigma(esn0, 1);

		if (ar.exist_arg({"dec-path"}))
			base_path = ar.get_arg({"dec-path"});

		params_fbg.get_headers(headers);
		params_dec.get_headers(headers);

		headers["dec"].push_back({"Base path", base_path});
	}
	else
		need_help = true;

	if (ar.exist_arg({"help", "h"}) || need_help)
	{
		ar.print_usage(arg_group);
		std::cout << "Powered by AFF3CT "
		          << "(v" << version_major() << "." << version_minor() << "." << version_release() << ")."
		          << std::endl;
		return EXIT_FAILURE;
	}

	int max_n_chars = 0;
	factory::Header::compute_max_n_chars(headers["fbg"], max_n_chars);
	factory::Header::compute_max_n_chars(headers["dec"], max_n_chars);

	// display configuration parameters
	std::cout << "# " << tools::format("-------------------------------------------------", tools::Style::BOLD) << std::endl;
	std::cout << "# " << tools::format("----  POLAR DECODER GENERATOR (with AFF3CT)  ----", tools::Style::BOLD) << std::endl;
	std::cout << "# " << tools::format("-------------------------------------------------", tools::Style::BOLD) << std::endl;
	std::cout << "# " << tools::format("Parameters :", tools::Style::BOLD | tools::Style::UNDERLINED)           << std::endl;

	if (headers["fbg"].size()) factory::Header::print_parameters("fbg", params_fbg.get_short_name(), headers["fbg"], max_n_chars);
	if (headers["dec"].size()) factory::Header::print_parameters("dec", params_dec.get_short_name(), headers["dec"], max_n_chars);

	if (!tools::is_power_of_2(params_dec.N_cw))
		throw std::invalid_argument("'N' has to be a power of 2 ('N' = " + std::to_string(params_dec.N_cw) + ").");

	if (arch != "GPP" && arch != "TTA")
		throw std::invalid_argument("Unsupported architecture. Valid architectures are GPP and TTA");

	// ----------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------- objects allocation
	// ----------------------------------------------------------------------------------------------------------------

	auto fb_generator = factory::Frozenbits_generator::build(params_fbg);

	// generate the frozen bits
	std::vector<bool> frozen_bits(params_dec.N_cw);
	fb_generator->generate(frozen_bits);

	// work only for SC or SCL and systematic encoding...
	std::string file_name;
	std::string source_suffix;
	if (arch == "GPP")
	{
		source_suffix = ".hpp";
		if (params_dec.type == "SCL")
			file_name  = "Decoder_polar_SCL_fast_CA_sys_N" + std::to_string(params_dec.N_cw) +
						 "_K" + std::to_string(params_dec.K) +
						 "_SNR" + std::to_string((int)(ebn0*10));
		else if (params_dec.type == "SC")
			file_name  = "Decoder_polar_SC_fast_sys_N"   + std::to_string(params_dec.N_cw) +
						 "_K"   + std::to_string(params_dec.K) +
					     "_SNR" + std::to_string((int)(ebn0*10));
	}
	else if (arch == "TTA")
	{
		source_suffix = ".cpp";
		if (params_dec.type == "SC")
			file_name  = "Decoder_simd_unrolled";
		else if (params_dec.type == "SCAN")
			file_name  = "Decoder_simd_scan";
	}

	// open the files
	std::fstream dec_file, short_dec_file, graph_file, short_graph_file;
	dec_file  .open((base_path + "/" + file_name + source_suffix).c_str(), std::ios_base::out);
	graph_file.open((base_path + "/" + file_name + ".dot"       ).c_str(), std::ios_base::out);

	// generator allocation
	std::vector<tools::Pattern_polar_i*> polar_patterns;
	generator::Generator_polar *generator = nullptr;
	Pattern_polar_i* pattern_tile;

	if (arch == "GPP")
	{
		if (params_dec.type == "SCL")
		{
			int idx_r0, idx_r1;
			polar_patterns = tools::nodes_parser<tools::Pattern_polar_SCL_r0,
					tools::Pattern_polar_SCL_r0_left,
					tools::Pattern_polar_SCL_r1,
					tools::Pattern_polar_SCL_rep,
					tools::Pattern_polar_SCL_rep_left,
					tools::Pattern_polar_SCL_spc,
					tools::Pattern_polar_SCL_std>(params_dec.polar_nodes, idx_r0, idx_r1);

			generator = new generator::Generator_polar_GPP_SCL_sys(params_dec.K, params_dec.N_cw, ebn0, frozen_bits,
															       polar_patterns, *polar_patterns[idx_r0],
															       *polar_patterns[idx_r1], dec_file, graph_file);
		}
		else if (params_dec.type == "SC")
		{
			short_dec_file  .open((base_path + "/" + file_name + ".short" + source_suffix).c_str(), std::ios_base::out);
			short_graph_file.open((base_path + "/" + file_name + ".short.dot"            ).c_str(), std::ios_base::out);

			int idx_r0, idx_r1;
			polar_patterns = tools::nodes_parser<tools::Pattern_polar_SC_r0,
					tools::Pattern_polar_SC_r0_left,
					tools::Pattern_polar_SC_r1,
					tools::Pattern_polar_SC_rep,
					tools::Pattern_polar_SC_rep_left,
					tools::Pattern_polar_SC_spc,
					tools::Pattern_polar_SC_std>(params_dec.polar_nodes, idx_r0, idx_r1);

			generator = new generator::Generator_polar_GPP_SC_sys(params_dec.K, params_dec.N_cw, ebn0, frozen_bits,
															  polar_patterns, *polar_patterns[idx_r0],
															  *polar_patterns[idx_r1], dec_file, short_dec_file,
															  graph_file, short_graph_file);
		}
		else
			throw std::invalid_argument("Unsupported type of decoder.");
	}
	else if (arch == "TTA")
	{
		if (params_dec.type == "SC")
		{
			short_dec_file  .open((base_path + "/" + file_name + ".short" + source_suffix).c_str(), std::ios_base::out);
			short_graph_file.open((base_path + "/" + file_name + ".short.dot"            ).c_str(), std::ios_base::out);

			int idx_r0, idx_r1;
			polar_patterns = tools::nodes_parser<tools::Pattern_polar_TTA_SC_r0,
					tools::Pattern_polar_TTA_SC_r0_left,
					tools::Pattern_polar_TTA_SC_r1,
					tools::Pattern_polar_TTA_SC_rep,
					tools::Pattern_polar_TTA_SC_rep_left,
					tools::Pattern_polar_TTA_SC_spc,
					tools::Pattern_polar_TTA_SC_std>(params_dec.polar_nodes, idx_r0, idx_r1);

			// add pattern_tile
			pattern_tile = new Pattern_polar_tile();
			polar_patterns.push_back(pattern_tile);

			generator = new generator::Generator_polar_TTA_SC_sys(params_dec.K, params_dec.N_cw, ebn0, frozen_bits,
															      polar_patterns, *polar_patterns[idx_r0],
															      *polar_patterns[idx_r1], dec_file, short_dec_file,
															      graph_file, short_graph_file);
		}
		else if (params_dec.type == "SCAN")
		{
			short_dec_file  .open((base_path + "/" + file_name + ".short" + source_suffix).c_str(), std::ios_base::out);
			short_graph_file.open((base_path + "/" + file_name + ".short.dot"            ).c_str(), std::ios_base::out);

			int idx_r0, idx_r1;
			polar_patterns = tools::nodes_parser<
			                                        tools::Pattern_polar_TTA_SCAN_r0,
					                                tools::Pattern_polar_TTA_SCAN_r0_left,
					                                tools::Pattern_polar_TTA_SCAN_r1,
					                                tools::Pattern_polar_TTA_SCAN_rep,
					                                tools::Pattern_polar_TTA_SCAN_rep_left,
					                                tools::Pattern_polar_TTA_SCAN_spc,
					                                tools::Pattern_polar_TTA_SCAN_std
					                            >(params_dec.polar_nodes, idx_r0, idx_r1);

			// add pattern_tile
			pattern_tile = new Pattern_polar_tile_scan();
			polar_patterns.push_back(pattern_tile);

			generator = new generator::Generator_polar_TTA_SCAN_sys(params_dec.K, params_dec.N_cw, params_dec.n_ite, 
				                                                    ebn0, frozen_bits, polar_patterns, 
				                                                    *polar_patterns[idx_r0], *polar_patterns[idx_r1], 
				                                                    dec_file, short_dec_file, graph_file, 
				                                                    short_graph_file);
		}
		else
			throw std::invalid_argument("Unsupported type of decoder.");
	}
	else
	{
		throw std::invalid_argument("Unsupported architecture. Valid architectures are GPP and TTA");
	}


	// ----------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------- polar decoder generation
	// ----------------------------------------------------------------------------------------------------------------
	generator->generate();

	// ----------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------- display some statistics
	// ----------------------------------------------------------------------------------------------------------------

	std::string tab = "   ";

	std::cerr << "#"                                                                                 << std::endl;
	std::cout << tools::format("General statistics:", tools::Style::BOLD | tools::Style::UNDERLINED) << std::endl;

	unsigned long n_nodes     = params_dec.N_cw -1;
	unsigned long n_nodes_gen = generator->get_n_generated_nodes();

	std::cout << tab << "Generated decoder file name = " << base_path << "/" << file_name << ".hpp" << std::endl;
	std::cout << tab << "Associate graph file name   = " << base_path << "/" << file_name << ".dot" << std::endl;
	std::cout << tab << "Nodes number before pruning = " << n_nodes                                 << std::endl;
	std::cout << tab << "Nodes number  after pruning = " << n_nodes_gen                             << std::endl;
	std::cout << tab << "Terminal nodes (alias pruning rules):"                                     << std::endl;
	for (unsigned p = 0; p < polar_patterns.size(); p++)
	{
		auto cur_pattern_SC = polar_patterns[p];
		if (cur_pattern_SC->is_terminal())
			std::cout << tab << tab << " - " << std::setw(11) << cur_pattern_SC->name() << ": "
			          << std::setw(5)
			          << generator->get_n_generated_nodes_by_pattern(typeid(*cur_pattern_SC).hash_code(), -1) 
			          << " / " << n_nodes_gen << std::endl;
	}
	std::cout << tab << "Non-terminal nodes (alias specialization rules):" << std::endl;
	for (unsigned p = 0; p < polar_patterns.size(); p++)
	{
		auto cur_pattern_SC = polar_patterns[p];
		if (!cur_pattern_SC->is_terminal())
			std::cout << tab << tab << " - " << std::setw(11) << cur_pattern_SC->name() << ": "
			          << std::setw(5)
			          << generator->get_n_generated_nodes_by_pattern(typeid(*cur_pattern_SC).hash_code(), -1) 
			          << " / " << n_nodes_gen << std::endl;
	}

	std::cout << std::endl;

	std::cout << tools::format("Per layer (graph depth) statistics:", tools::Style::BOLD | tools::Style::UNDERLINED) 
              << std::endl;
	auto m = (int)std::ceil(std::log2(params_dec.N_cw));
	for (auto d = 0; d < m +1; d++)
	{
		n_nodes     = (unsigned long)std::pow(2, d);
		n_nodes_gen = generator->get_n_generated_nodes(d);

		std::cout << tab        << "* Graph depth = " << d                         << std::endl;
		std::cout << tab << tab << "Sub-code length = " << std::pow(2, m -d)       << std::endl;
		std::cout << tab << tab << "Nodes number before pruning = " << n_nodes     << std::endl;
		std::cout << tab << tab << "Nodes number  after pruning = " << n_nodes_gen << std::endl;
		std::cout << tab << tab << "Terminal nodes (alias pruning rules)"          << std::endl;
		for (unsigned p = 0; p < polar_patterns.size(); p++)
		{
			auto cur_pattern_SC = polar_patterns[p];
			if (cur_pattern_SC->is_terminal())
				std::cout << tab << tab << tab << " - " << std::setw(11) << cur_pattern_SC->name() << ": "
				          << std::setw(5)
				          << generator->get_n_generated_nodes_by_pattern(typeid(*cur_pattern_SC).hash_code(), d) 
				          << " / " << n_nodes_gen << std::endl;
		}
		std::cout << tab << tab << "Non-terminal nodes (alias specialization rules):" << std::endl;
		for (unsigned p = 0; p < polar_patterns.size(); p++)
		{
			auto cur_pattern_SC = polar_patterns[p];
			if (!cur_pattern_SC->is_terminal())
				std::cout << tab << tab << tab << " - " << std::setw(11) << cur_pattern_SC->name() << ": "
				          << std::setw(5)
				          << generator->get_n_generated_nodes_by_pattern(typeid(*cur_pattern_SC).hash_code(), d) 
				          << " / " << n_nodes_gen << std::endl;
		}
		if (d < m)
			std::cout << std::endl;
		else
			std::cerr << "#" << std::endl;
	}

	// ----------------------------------------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------------------- objects deallocation
	// ----------------------------------------------------------------------------------------------------------------

	if (dec_file        .is_open()) dec_file        .close();
	if (short_dec_file  .is_open()) short_dec_file  .close();
	if (graph_file      .is_open()) graph_file      .close();
	if (short_graph_file.is_open()) short_graph_file.close();

	if (generator    != nullptr) delete generator;
	if (fb_generator != nullptr) delete fb_generator;

	for (unsigned i = 0; i < polar_patterns.size(); i++)
		delete polar_patterns[i]; // memory leak possible with patter_SC_rate0 and 1 (but OSEF) and maybe tile <3


	return EXIT_SUCCESS;
}
