#ifndef PATTERN_POLAR_TTA_SC_RATE_0_LEFT_HPP_
#define PATTERN_POLAR_TTA_SC_RATE_0_LEFT_HPP_

#include <aff3ct.hpp>

namespace aff3ct
{
namespace tools
{
class Pattern_polar_TTA_SC_r0_left : public Pattern_polar_r0_left
{
protected:
	Pattern_polar_TTA_SC_r0_left(const int &N, const Binary_node<Pattern_polar_i>* node,
	                         const int min_level = 1, const int max_level = -1)
	: Pattern_polar_r0_left(N, node, min_level, max_level)
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
	Pattern_polar_TTA_SC_r0_left(const int min_level = 1, const int max_level = -1)
	: Pattern_polar_r0_left(min_level, max_level) {}

	virtual ~Pattern_polar_TTA_SC_r0_left() {}

	virtual Pattern_polar_i* alloc(const int &N, const Binary_node<Pattern_polar_i>* node) const
	{
		return new Pattern_polar_TTA_SC_r0_left(N, node, this->min_level, this->max_level);
	}

	virtual std::string apply_f(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		return "";
	}

	virtual std::string apply_g(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);
		if (str_off_s.empty()) str_off_s = std::to_string(this->off_s);

		std::stringstream stream;

		if (this->si_2 <= 64)
		{
			// TODO only one load ?
			stream << "_TCE_LDOFF(" << this->off_l << ", l_a);" << std::endl;

			if (this->si_2 == 64)
				stream << tab << "_TCE_LDOFF(" << this->off_l + 64 << ", l_b);" << std::endl;
			else if (this->si_2 == 32)
				stream << tab << "_TCE_LDOFF_8X32(" << this->off_l + 32 << ", l_b);" << std::endl;
			else if (this->si_2 == 16)
				stream << tab << "_TCE_LDOFF_8X16(" << this->off_l + 16 << ", l_b);" << std::endl;
			else if (this->si_2 == 8)
				stream << tab << "_TCE_LDOFF_8X8(" << this->off_l + 8 << ", l_b);" << std::endl;

			if (this->si_2 != 64)
				stream << tab << "_TCE_ALIGN_8X8(s[" << (off_s >> 6) << "]," << ((off_s >> 3) & 7) << ", temp_s);" << std::endl;
			else
				stream << tab << "_TCE_POLAR_G8X64(l_a, l_b, s[" << (off_s >> 6) << "], l_c);" << std::endl;

			stream << tab << "_TCE_POLAR_G8X64(l_a, l_b, temp_s, l_c);" << std::endl;
			
			if (! this->node->get_right()->get_c()->is_terminal())
				if (this->si_2 != 64)
					stream << tab << "_TCE_STOFF(" << this->off_l + 64 << ", l_c);" << std::endl;
				else
					stream << tab << "_TCE_STOFF(" << this->off_l + this->size << ", l_c);" << std::endl;
			// TODO do not store if last leaf
		}
		else // n_elm
		{
			for (auto i = 0; i < this->si_2; i += 64)
			{	if (i)
					stream << tab;
				stream        << "_TCE_LDOFF(" << this->off_l + i              << ", l_a);" << std::endl;
				stream << tab << "_TCE_LDOFF(" << this->off_l + i + this->si_2 << ", l_b);" << std::endl;
				stream << tab << "_TCE_POLAR_G8X64(l_a, l_b, s[" << ((off_s >> 6) + (i >> 6)) << "], l_c);" << std::endl;
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
		if (this->si_2 < 64)
		{
			stream << "_TCE_PS_COMBINE(s[" << (off_s >> 6) << "]," << (off_s >> 3) << ", " << (this->si_2 >> 3) <<", ";
			stream << "s[" << (off_s >> 6) << "]);" << std::endl;
		}
		else
		{
			for (auto i = 0; i < (this->si_2 >> 6); i++)
			{
				if(i)
					stream << tab;
				stream << "temp_s";
				stream << " = ";
				stream << "s[" << (this->off_s >> 6) + i << "]";
				stream << " ^ ";
				stream << "s[" << (((this->off_s +  + this->si_2) >> 6) + i) << "];" << std::endl;


				stream << tab << "s[" << (this->off_s >> 6) + i << "]";
				stream << " = ";
				stream << "temp_s;" << std::endl;

			}
		}

		return stream.str();
	}
};
}
}

#endif /* PATTERN_POLAR_TTA_SC_RATE_0_LEFT_HPP_ */
