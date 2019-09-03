#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

// AFF3CT header
#include <aff3ct.hpp>

#include "Generator/Polar/SC/Generator_polar_SC_sys.hpp"
#include "Generator/Polar/SCL/Generator_polar_SCL_sys.hpp"

#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_r0_left.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_r1.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_rep_left.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_spc.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_rep.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_r0.hpp"
#include "Tools/Code/Polar/Patterns/SC/Pattern_polar_SC_std.hpp"

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

	std::string base_path = ".";
	tools::Argument_map_info args;

	args.add({"help", "h"},
		tools::None(),
		"print this help.");

	factory::Frozenbits_generator::parameters params_fbg;
	factory::Decoder_polar       ::parameters params_dec;

	tools::Argument_map_group grps;
	grps[params_fbg.get_prefix()] = params_fbg.get_short_name() + " parameters";
	grps[params_dec.get_prefix()] = params_dec.get_short_name() + " parameters";

	params_fbg.get_description(args);
	params_dec.get_description(args);

	args.add({params_dec.get_prefix()+"-path"},
		tools::Folder(tools::openmode::read),
		"Base path where the decoder will be generated (default = current dir).");

	args.erase({params_fbg.get_prefix()+"-sigma"           });
	args.erase({params_dec.get_prefix()+"-cw-size",     "N"});
	args.erase({params_dec.get_prefix()+"-info-bits",   "K"});
	args.erase({params_dec.get_prefix()+"-fra",         "F"});
	args.erase({params_dec.get_prefix()+"-implem"          });
	args.erase({params_dec.get_prefix()+"-ite",         "i"});
	args.erase({params_dec.get_prefix()+"-lists",       "L"});
	args.erase({params_dec.get_prefix()+"-no-sys"          });
	args.erase({params_dec.get_prefix()+"-partial-adaptive"});
	args.erase({params_dec.get_prefix()+"-simd"            });
	args.erase({params_dec.get_prefix()+"-flips"           });
	args.erase({params_dec.get_prefix()+"-hamming"         });
	args.erase({params_dec.get_prefix()+"-type",        "D"});
	args.erase({params_dec.get_prefix()+"-seed",           });

	args.add({params_dec.get_prefix()+"-type", "D"},
		tools::Text(tools::Including_set("SC", "SCL")),
		"Set the type of decoder to generate (or to unroll).");

	auto const_argv = const_cast<const char**>(argv);
	tools::Argument_handler ah(argc, const_argv);
	tools::Argument_map_value arg_vals;
	std::vector<std::string> cmd_warn, cmd_error;
	std::map<std::string,factory::header_list> headers;

	arg_vals = ah.parse_arguments(args, cmd_warn, cmd_error);

	try
	{
		params_fbg.store(arg_vals);
		params_dec.K    = params_fbg.K;
		params_dec.N_cw = params_fbg.N_cw;
		params_dec.store(arg_vals);

		if (arg_vals.exist({params_dec.get_prefix()+"-path"}))
			base_path = arg_vals.to_folder({params_dec.get_prefix()+"-path"});

		params_fbg.get_headers(headers);
		params_dec.get_headers(headers);

		headers[params_dec.get_prefix()].push_back({"Base path", base_path});
	}
	catch (const std::exception& e)
	{
		auto save = tools::exception::no_backtrace;
		tools::exception::no_backtrace = true;
		cmd_error.emplace_back(e.what());
		tools::exception::no_backtrace = save;
	}

	const bool display_help = arg_vals.exist({"help", "h"});
	if (display_help)
	{
		ah.print_help(args, grps, false);
		return EXIT_FAILURE;
	}

	// print usage
	if (!cmd_error.empty() && !display_help)
		ah.print_usage(args);

	// print the errors
	if (!cmd_error.empty()) std::cerr << std::endl;
	for (unsigned e = 0; e < cmd_error.size(); e++)
		std::cerr << rang::tag::error << cmd_error[e] << std::endl;

	// print the help tags
	if (!cmd_error.empty() && !display_help)
	{
		tools::Argument_tag help_tag = {"help", "h"};

		std::string message = "For more information please display the help (\"";
		message += tools::Argument_handler::print_tag(help_tag) += "\").";

		std::cerr << std::endl << rang::tag::info << message << std::endl;

		return EXIT_FAILURE;
	}

	int max_n_chars = 0;
	factory::Header::compute_max_n_chars(headers[params_fbg.get_prefix()], max_n_chars);
	factory::Header::compute_max_n_chars(headers[params_dec.get_prefix()], max_n_chars);

	// display configuration parameters
	std::cout << "# " << rang::style::bold << "-------------------------------------------------" << std::endl;
	std::cout << "# " << rang::style::bold << "----  POLAR DECODER GENERATOR (with AFF3CT)  ----" << std::endl;
	std::cout << "# " << rang::style::bold << "-------------------------------------------------" << std::endl;
	std::cout << "# " << rang::style::bold << rang::style::underline << "Parameters:" << rang::style::reset << std::endl;

	if (headers["fbg"].size())
		factory::Header::print_parameters(params_fbg.get_prefix(),
		                                  params_fbg.get_short_name(),
		                                  headers[params_fbg.get_prefix()],
		                                  max_n_chars);
	if (headers["dec"].size())
		factory::Header::print_parameters(params_dec.get_prefix(),
		                                  params_dec.get_short_name(),
		                                  headers[params_dec.get_prefix()],
		                                  max_n_chars);

	if (!tools::is_power_of_2(params_dec.N_cw))
		throw std::invalid_argument("'N' has to be a power of 2 ('N' = " + std::to_string(params_dec.N_cw) + ").");

	// ----------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------- objects allocation
	// ----------------------------------------------------------------------------------------------------------------

	auto fb_generator = factory::Frozenbits_generator::build(params_fbg);
	const auto ebn0 = params_fbg.noise;
	fb_generator->set_noise(tools::Sigma<float>(tools::esn0_to_sigma(tools::ebn0_to_esn0(ebn0, params_dec.R))));

	// generate the frozen bits
	std::vector<bool> frozen_bits(params_dec.N_cw);
	fb_generator->generate(frozen_bits);

	// work only for SC or SCL and systematic encoding...
	std::string file_name;
	if (params_dec.type == "SCL")
		file_name  = "Decoder_polar_SCL_fast_CA_sys_N" + std::to_string(params_dec.N_cw) +
		                                          "_K" + std::to_string(params_dec.K) +
		                                        "_SNR" + std::to_string((int)(ebn0*10));
	else if (params_dec.type == "SC")
		file_name  = "Decoder_polar_SC_fast_sys_N"   + std::to_string(params_dec.N_cw) +
		                                      "_K"   + std::to_string(params_dec.K) +
		                                      "_SNR" + std::to_string((int)(ebn0*10));

	// open the files
	std::fstream dec_file, short_dec_file, graph_file, short_graph_file;
	dec_file  .open((base_path + "/" + file_name + ".hpp").c_str(), std::ios_base::out);
	graph_file.open((base_path + "/" + file_name + ".dot").c_str(), std::ios_base::out);

	// generator allocation
	std::vector<tools::Pattern_polar_i*> polar_patterns;
	generator::Generator_polar *generator = nullptr;
	if (params_dec.type == "SCL")
	{
		int idx_r0, idx_r1;
		polar_patterns = tools::Nodes_parser<tools::Pattern_polar_SCL_r0,
		                                     tools::Pattern_polar_SCL_r0_left,
		                                     tools::Pattern_polar_SCL_r1,
		                                     tools::Pattern_polar_SCL_rep,
		                                     tools::Pattern_polar_SCL_rep_left,
		                                     tools::Pattern_polar_SCL_spc,
		                                     tools::Pattern_polar_SCL_std>
		                                     ::parse_ptr(params_dec.polar_nodes, idx_r0, idx_r1);

		generator = new generator::Generator_polar_SCL_sys(params_dec.K, params_dec.N_cw, ebn0, frozen_bits,
		                                                   polar_patterns, idx_r0, idx_r1, dec_file, graph_file);
	}
	else if (params_dec.type == "SC")
	{
		short_dec_file  .open((base_path + "/" + file_name + ".short.hpp").c_str(), std::ios_base::out);
		short_graph_file.open((base_path + "/" + file_name + ".short.dot").c_str(), std::ios_base::out);

		int idx_r0, idx_r1;
		polar_patterns = tools::Nodes_parser<tools::Pattern_polar_SC_r0,
		                                     tools::Pattern_polar_SC_r0_left,
		                                     tools::Pattern_polar_SC_r1,
		                                     tools::Pattern_polar_SC_rep,
		                                     tools::Pattern_polar_SC_rep_left,
		                                     tools::Pattern_polar_SC_spc,
		                                     tools::Pattern_polar_SC_std>
		                                     ::parse_ptr(params_dec.polar_nodes, idx_r0, idx_r1);

		generator = new generator::Generator_polar_SC_sys(params_dec.K, params_dec.N_cw, ebn0, frozen_bits,
		                                                  polar_patterns, idx_r0, idx_r1, dec_file, short_dec_file,
		                                                  graph_file, short_graph_file);
	}
	else
		throw std::invalid_argument("Unsupported type of decoder.");

	// ----------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------- polar decoder generation
	// ----------------------------------------------------------------------------------------------------------------

	generator->generate();

	// ----------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------- display some statistics
	// ----------------------------------------------------------------------------------------------------------------

	std::string tab = "   ";

	std::cerr << "#"                                                                  << std::endl;
	std::cout << rang::style::bold << rang::style::underline << "General statistics:" << std::endl;
	std::cout << rang::style::reset;

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

	std::cout << rang::style::bold << rang::style::underline << "Per layer (graph depth) statistics:"
              << rang::style::reset << std::endl;
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

	// Automatically deleted by the "tools::Pattern_polar_parser" destructor
	// for (unsigned i = 0; i < polar_patterns.size(); i++)
	// 	delete polar_patterns[i]; // memory leak possible with patter_SC_rate0 and 1 (but OSEF)

	return EXIT_SUCCESS;
}
