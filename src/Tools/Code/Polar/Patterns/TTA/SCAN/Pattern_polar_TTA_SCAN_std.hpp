#ifndef PATTERN_POLAR_TTA_SCAN_STANDARD_HPP_
#define PATTERN_POLAR_TTA_SCAN_STANDARD_HPP_

#include <aff3ct.hpp>

namespace aff3ct
{
namespace tools
{
class Pattern_polar_TTA_SCAN_std : public Pattern_polar_std
{
protected:
	Pattern_polar_TTA_SCAN_std(const int &N, const Binary_node<Pattern_polar_i>* node)
	: Pattern_polar_std(N, node)
	{
		auto n_elm_2 = this->N / 2;
		auto local_off_l = 0;

		for (auto layer = this->m; layer > (this->m - node->get_depth()); layer--)
		{
			if ((n_elm_2 * 2) > 64)
				local_off_l += n_elm_2 * 2;
			else
				local_off_l += 64;
			n_elm_2 /= 2;
		}

		const int *p_off_l = &off_l;
		*const_cast<int*>(p_off_l) = local_off_l;
	}

public:
	Pattern_polar_TTA_SCAN_std() : Pattern_polar_std() {}

	virtual ~Pattern_polar_TTA_SCAN_std() {}

	virtual Pattern_polar_i* alloc(const int &N, const Binary_node<Pattern_polar_i>* node) const
	{
		return new Pattern_polar_TTA_SCAN_std(N, node);
	}



	virtual std::string apply_f(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);

		std::stringstream stream;

		if (this->si_2 <= 32)
		{
			stream << "_TCE_LDOFF(" << str_off_l << ", l_b);" << std::endl;
			stream << tab << "_TCE_ROTLELEM_8X64(l_b, " << this->si_2 << ", l_b);" << std::endl;
			stream << tab << "_TCE_LDOFF(" << str_off_l << ", l_a);" << std::endl;
			if (this->si_2 == 32)
			{
				stream << tab << "_TCE_LDOFF_B_8X32(" << (this->m - this->rev_depth + 1) * this->N + this->off_s + this->si_2 << ", b_a);" << std::endl;
			}
			else if (this->si_2  == 16)
			{
				stream << tab << "_TCE_LDOFF_B_8X16(" << (this->m - this->rev_depth + 1) * this->N + this->off_s + this->si_2 << ", b_a);" << std::endl;
			}
			else if (this->si_2 == 8)
			{
				int off_b = (this->m - this->rev_depth + 1) * this->N + (this->off_s + this->si_2) * 4;
				stream << tab << "_TCE_LDOFF_B_8X8(" << off_b << ", b_a);" << std::endl;
			}
			stream << tab << "_TCE_POLAR_F_SCAN8X64(l_a, l_b, b_a, l_c);" << std::endl;
			stream << tab << "_TCE_STOFF(" << str_off_l << " + 64, l_c);" << std::endl;
		}
		else // n_elm
		{
			for (auto i = 0; i < this->si_2; i += 64)
			{	if (i)
					stream << tab;
				stream        << "_TCE_LDOFF(" << this->off_l + i              << ", l_a);" << std::endl;
				stream << tab << "_TCE_LDOFF(" << this->off_l + i + this->si_2 << ", l_b);" << std::endl;
				stream << tab << "_TCE_LDOFF_B(" << (this->m - this->rev_depth + 1) * this->N + this->off_s + this->si_2 + i  << ", b_a);" << std::endl;
				stream << tab << "_TCE_POLAR_F_SCAN8X64(l_a, l_b, b_a, l_c);" << std::endl;
				stream << tab << "_TCE_STOFF(" << this->off_l + i + this->size << ", l_c);" << std::endl;
			}
		}


		return stream.str();
	}

	virtual std::string apply_g(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);
		if (str_off_s.empty()) str_off_s = std::to_string(this->off_s);

		std::stringstream stream;
		if (this->si_2 <= 32)
		{

			stream << "_TCE_LDOFF(" << str_off_l << ", l_b);" << std::endl;
			stream << tab << "_TCE_ROTLELEM_8X64(l_b, " << this->si_2 << ", l_b);" << std::endl;
			stream << tab << "_TCE_LDOFF(" << str_off_l << ", l_a);" << std::endl;
			if (this->si_2 == 32)
			{
				stream << tab << "_TCE_LDOFF_B_8X32(" << (this->m - this->rev_depth + 1) * this->N + this->off_s << ", b_a);" << std::endl;
			}
			else if (this->si_2 == 16)
			{
				stream << tab << "_TCE_LDOFF_B_8X16(" << (this->m - this->rev_depth + 1) * this->N + this->off_s << ", b_a);" << std::endl;
			}
			else if (this->si_2 == 8)
			{
				int off_b = (this->m - this->rev_depth + 1) * this->N + this->off_s * 4;
				stream << tab << "_TCE_LDOFF_B_8X8(" << off_b << ", b_a);" << std::endl;
			}
			stream << tab << "_TCE_POLAR_F_SCAN8X64(l_a, l_b, b_a, l_c);" << std::endl;
			stream << tab << "_TCE_STOFF(" << str_off_l << " + 64, l_c);" << std::endl;
		}
		else // n_elm
		{
			for (auto i = 0; i < this->si_2; i += 64)
			{	if (i)
					stream << tab;
				stream        << "_TCE_LDOFF(" << this->off_l + i              << ", l_a);" << std::endl;
				stream << tab << "_TCE_LDOFF(" << this->off_l + i + this->si_2 << ", l_b);" << std::endl;
				stream << tab << "_TCE_LDOFF_B(" << (this->m - this->rev_depth + 1) * this->N + this->off_s + i  << ", b_a);" << std::endl;
				stream << tab << "_TCE_POLAR_G_SCAN8X64(l_a, l_b, b_a, l_c);" << std::endl;
				stream << tab << "_TCE_STOFF(" << this->off_l + i + this->size << ", l_c);" << std::endl;
			}
		}


		return stream.str();
	}

	virtual std::string apply_h(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);
		if (str_off_s.empty()) str_off_s = std::to_string(this->off_s);

		std::stringstream stream;
		if (this->rev_depth == this->m)
			return "";
		else if (this->si_2 == 32)
		{
			stream        << "_TCE_LDOFF_B_8X32(" << (this->m - this->rev_depth + 1) * this->N + this->off_s               << ", b_a);" << std::endl;
			stream << tab << "_TCE_LDOFF_B_8X32(" << (this->m - this->rev_depth + 1) * this->N + this->off_s + this->si_2  << ", b_b);" << std::endl;
			stream << tab << "_TCE_LDOFF("   << str_off_l << ", l_a);"                                                                  << std::endl;
			stream << tab << "_TCE_ROTLELEM_8X64(l_a, " << this->si_2 << ", l_b);"                                                      << std::endl;
			stream << tab << "_TCE_POLAR_F_SCAN8X64(b_a, b_b, l_b, b_c);"                                                               << std::endl;
			stream << tab << "_TCE_STOFF_B_8X32(" << (this->m - this->rev_depth    ) * this->N + this->off_s               << ", b_c);" << std::endl;
			stream << tab << "_TCE_POLAR_G_SCAN8X64(b_a, b_b, l_a, b_c);"                                                               << std::endl;
			stream << tab << "_TCE_STOFF_B_8X32(" << (this->m - this->rev_depth    ) * this->N + this->off_s + this->si_2  << ", b_c);" << std::endl;
		}
		else if (this->si_2 == 16)
		{
			stream        << "_TCE_LDOFF_B_8X16(" << (this->m - this->rev_depth + 1) * this->N + this->off_s               << ", b_a);" << std::endl;
			stream << tab << "_TCE_LDOFF_B_8X16(" << (this->m - this->rev_depth + 1) * this->N + this->off_s + this->si_2  << ", b_b);" << std::endl;
			stream << tab << "_TCE_LDOFF("   << str_off_l << ", l_a);"                                                                  << std::endl;
			stream << tab << "_TCE_ROTLELEM_8X64(l_a, " << this->si_2 << ", l_b);"                                                      << std::endl;
			stream << tab << "_TCE_POLAR_F_SCAN8X64(b_a, b_b, l_b, b_c);"                                                               << std::endl;
			stream << tab << "_TCE_STOFF_B_8X16(" << (this->m - this->rev_depth    ) * this->N + this->off_s               << ", b_c);" << std::endl;
			stream << tab << "_TCE_POLAR_G_SCAN8X64(b_a, b_b, l_a, b_c);"                                                               << std::endl;
			stream << tab << "_TCE_STOFF_B_8X16(" << (this->m - this->rev_depth    ) * this->N + this->off_s + this->si_2  << ", b_c);" << std::endl;
		}
		else if (this->si_2 == 8)
		{
			int off_b_a = (this->m - this->rev_depth + 1) * this->N + this->off_s * 4;
			int off_b_b = (this->m - this->rev_depth + 1) * this->N + (this->off_s + this->si_2) * 4;
			stream        << "_TCE_LDOFF_B_8X8(" << off_b_a << ", b_a);"                                                               << std::endl;
			stream << tab << "_TCE_LDOFF_B_8X8(" << off_b_b << ", b_b);"                                                               << std::endl;
			stream << tab << "_TCE_LDOFF("   << str_off_l << ", l_a);"                                                                 << std::endl;
			stream << tab << "_TCE_ROTLELEM_8X64(l_a, " << this->si_2 << ", l_b);"                                                     << std::endl;
			stream << tab << "_TCE_POLAR_F_SCAN8X64(b_a, b_b, l_b, b_c);"                                                              << std::endl;
			stream << tab << "_TCE_STOFF_B_8X8(" << (this->m - this->rev_depth    ) * this->N + this->off_s               << ", b_c);" << std::endl;
			stream << tab << "_TCE_POLAR_G_SCAN8X64(b_a, b_b, l_a, b_c);"                                                              << std::endl;
			stream << tab << "_TCE_STOFF_B_8X8(" << (this->m - this->rev_depth    ) * this->N + this->off_s + this->si_2  << ", b_c);" << std::endl;
		}
		else
		{
			for (auto i = 0; i < this->si_2; i += 64)
			{
				if(i)
					stream << tab;
				stream        << "_TCE_LDOFF_B(" << (this->m - this->rev_depth + 1) * this->N + this->off_s              + i  << ", b_a);" << std::endl;
				stream << tab << "_TCE_LDOFF_B(" << (this->m - this->rev_depth + 1) * this->N + this->off_s + this->si_2 + i  << ", b_b);" << std::endl;
				stream << tab << "_TCE_LDOFF("   << this->off_l + i + this->si_2 << ", l_c);" << std::endl;
				stream << tab << "_TCE_POLAR_F_SCAN8X64(b_a, b_b, l_c, b_c);" << std::endl;
				stream << tab << "_TCE_STOFF_B(" << (this->m - this->rev_depth    ) * this->N + this->off_s              + i << ", b_c);" << std::endl;
				stream << tab << "_TCE_LDOFF(" << this->off_l + i                << ", l_c);" << std::endl;
				stream << tab << "_TCE_POLAR_G_SCAN8X64(b_a, b_b, l_c, b_c);" << std::endl;
				stream << tab << "_TCE_STOFF_B(" << (this->m - this->rev_depth    ) * this->N + this->off_s + this->si_2 + i << ", b_c);" << std::endl;
			}
		}

		return stream.str();
	}
};
}
}

#endif /* PATTERN_POLAR_TTA_SCAN_STANDARD_HPP_ */
