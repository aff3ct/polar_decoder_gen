#ifndef PATTERN_POLAR_TTA_SC_STANDARD_HPP_
#define PATTERN_POLAR_TTA_SC_STANDARD_HPP_

#include <aff3ct.hpp>

namespace aff3ct
{
namespace tools
{
class Pattern_polar_TTA_SC_std : public Pattern_polar_std
{
protected:
	Pattern_polar_TTA_SC_std(const int &N, const Binary_node<Pattern_polar_i>* node)
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
	Pattern_polar_TTA_SC_std() : Pattern_polar_std() {}

	virtual ~Pattern_polar_TTA_SC_std() {}

	virtual Pattern_polar_i* alloc(const int &N, const Binary_node<Pattern_polar_i>* node) const
	{
		return new Pattern_polar_TTA_SC_std(N, node);
	}

	virtual std::string apply_f(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);

		std::stringstream stream;

		if (this->si_2 < 64)
		{
			// TODO only one load ?
			stream << "_TCE_LDOFF(" << str_off_l << ", l_b);" << std::endl;
			stream << tab << "_TCE_ROTLELEM_8X64(l_b, " << this->si_2 << ", l_b);" << std::endl;
			stream << tab << "_TCE_LDOFF(" << str_off_l << ", l_a);" << std::endl;
			stream << tab << "_TCE_POLAR_F8X64(l_a, l_b, l_c);" << std::endl;
			stream << tab << "_TCE_STOFF(" << str_off_l << " + 64, l_c);" << std::endl;
			// TODO do not store if last leaf
			// TODO is it necessary to store at all when size < 64 ?
		}
		else // n_elm
		{

		}


		return stream.str();
	}

	virtual std::string apply_g(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);
		if (str_off_s.empty()) str_off_s = std::to_string(this->off_s);

		std::stringstream stream;

		if (this->si_2 < 64)
		{
			// TODO only one load ?
			stream << "_TCE_LDOFF(" << str_off_l << ", l_a);" << std::endl;
			stream << tab << "_TCE_LDOFF(" << str_off_l << ", l_b);" << std::endl;
			stream << tab << "_TCE_ALIGN_8X8(s[" << (off_s >> 6) << "]," << ((off_s >> 3) & 7) << ", temp_s);" << std::endl;
			stream << tab << "_TCE_ROTLELEM_8X64(l_b, " << this->si_2 << ", l_b);" << std::endl;
			stream << tab << "_TCE_POLAR_G8X64(l_a, l_b, temp_s, l_c);" << std::endl;
			stream << tab << "_TCE_STOFF(" << str_off_l << " + 64, l_c);" << std::endl;
			// TODO do not store if last leaf
			// TODO is it necessary to store at all when size < 64 ?
		}
		else // n_elm
		{

		}


		return stream.str();
	}

	virtual std::string apply_h(std::string start_indent = "", std::string str_off_l = "", std::string str_off_s = "") const
	{
		if (str_off_l.empty()) str_off_l = std::to_string(this->off_l);
		if (str_off_s.empty()) str_off_s = std::to_string(this->off_s);


		std::stringstream stream;
		stream << "_TCE_PS_COMBINE(s[" << (off_s >> 6) << "]," << (off_s >> 3) << ", " << (this->si_2 >> 3) <<", ";
		stream << "s[" << (off_s >> 6) << "]);" << std::endl;

		return stream.str();
	}
};
}
}

#endif /* PATTERN_POLAR_TTA_SC_STANDARD_HPP_ */
