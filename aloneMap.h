/*	Copyright (C) 2004-2007 Garrett A. Kajmowicz
	This file is part of the uClibc++ Library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/



#include <memory>
#include <utility.h>
#include <iterator>
#include <deque>
#include <functional>
#include <associative_base>


#ifndef __STD_HEADER_ALONE_MAP
#define __STD_HEADER_ALONE_MAP

#pragma GCC visibility push(default)

namespace std{


template<class Key, class T, class Compare = less<Key>, class Allocator = allocator<T> > class aloneMap;
template<class Key, class T, class Compare = less<Key>, class Allocator = allocator<T> > class aloneMultimap;


	//Compare the keys of the two items
/*	template<class Key, class T, class Compare, class Allocator> class _UCXXEXPORT
		__base_map<Key, T, Compare, Allocator>::value_compare : public binary_function<
			typename map<Key, T, Compare, Allocator>::value_type,
			typename map<Key, T, Compare, Allocator>::value_type,
		bool>
	{
		friend class __base_map<Key, T, Compare, Allocator>;
	protected:
		Compare comp;
		value_compare(Compare c) : comp(c) { }
		~value_compare() {  }
	public:
		bool operator()(const value_type& x, const value_type& y) const {
			return comp(x.first, y.first);
		}
	};
*/

//	value_compare value_comp() const;



/* This is the implementation for the map container.  As noted above, it deviates
 * from ISO spec by deriving from a base class in order to reduce code redundancy.
 * More code could be reduced by convirting to virtual functions (thus allowing
 * much of the erase and insert code to be duplicated), but that would deviate from
 * the specifications too much to be worth the risk.
 */



//Implementation of map


template<class Key, class T, class Compare, class Allocator> class _UCXXEXPORT aloneMap
	: public __single_associative<Key, alone_pair<Key, T>, Compare, Allocator>
{
		//Default value of allocator does not meet C++ standard specs, but it works for this library
		//Deal with it

public:

	typedef	__single_associative<Key, alone_pair<Key, T>, Compare, Allocator>	base;
	typedef T 								mapped_type;
	typedef typename base::key_type						key_type;
	typedef typename base::value_type					value_type;
	typedef typename base::key_compare					key_compare;
	typedef typename base::allocator_type					allocator_type;
	typedef typename base::reference					reference;
	typedef typename base::const_reference					const_reference;
	typedef typename base::iterator						iterator;
	typedef typename base::const_iterator					const_iterator;
	typedef typename base::size_type					size_type;
	typedef typename base::difference_type					difference_type;
	typedef typename base::pointer						pointer;
	typedef typename base::const_pointer					const_pointer;
	typedef typename base::reverse_iterator					reverse_iterator;
	typedef typename base::const_reverse_iterator				const_reverse_iterator;

	static const key_type v_t_k(const value_type v){
		return v.first;
	}

//	using base::value_compare;

	explicit aloneMap(const Compare& comp = Compare(), const Allocator& al = Allocator())
		: base(comp, al, v_t_k) {  }

	template <class InputIterator> aloneMap(InputIterator first, InputIterator last,
		const Compare& comp = Compare(), const Allocator& al = Allocator())
		: base(first, last, comp, al, v_t_k) {  }

	aloneMap(const aloneMap<Key,T,Compare,Allocator>& x) : base(x) {  }
	~aloneMap() {  }

	using base::operator=;
	using base::operator==;
	using base::operator!=;

	using base::insert;
	using base::erase;

	using base::begin;
	using base::end;
	using base::rbegin;
	using base::rend;

	using base::empty;
	using base::size;
	using base::max_size;

	using base::find;
	using base::count;
	using base::lower_bound;
	using base::upper_bound;
	using base::equal_range;
	using base::swap;

	reference operator[](const key_type& k){
		iterator i = lower_bound(k);
		if (i == end() || base::c(k, i->first)) {
			i = insert(make_alone_pair(k, T())).first;
		}
		return i->second;
	}

protected:
	using base::backing;
};


//Implementation of multimap


template<class Key, class T, class Compare, class Allocator> class _UCXXEXPORT aloneMultimap
	: public __multi_associative<Key, alone_pair<Key, T>, Compare, Allocator>

{
		//Default value of allocator does not meet C++ standard specs, but it works for this library
		//Deal with it
public:

	typedef	__multi_associative<Key, alone_pair<Key, T>, Compare, Allocator>	base;
	typedef T 								mapped_type;
	typedef typename base::key_type						key_type;
	typedef typename base::value_type					value_type;
	typedef typename base::key_compare					key_compare;
	typedef typename base::allocator_type					allocator_type;
	typedef typename base::reference					reference;
	typedef typename base::const_reference					const_reference;
	typedef typename base::iterator						iterator;
	typedef typename base::const_iterator					const_iterator;
	typedef typename base::size_type					size_type;
	typedef typename base::difference_type					difference_type;
	typedef typename base::pointer						pointer;
	typedef typename base::const_pointer					const_pointer;
	typedef typename base::reverse_iterator					reverse_iterator;
	typedef typename base::const_reverse_iterator				const_reverse_iterator;

	static const key_type v_t_k(const value_type v){
		return v.first;
	}

	explicit aloneMultimap(const Compare& comp = Compare(), const Allocator& al = Allocator())
		: base(comp, al, v_t_k) {  }

	template <class InputIterator> aloneMultimap(InputIterator first, InputIterator last,
		const Compare& comp = Compare(), const Allocator& al = Allocator())
		: base(first, last, comp, al, v_t_k) {  }


	aloneMultimap(const aloneMultimap<Key,T,Compare,Allocator>& x) : base(x) {  }
	~aloneMultimap() {  }

	using base::operator=;
	using base::operator==;
	using base::operator!=;

	using base::insert;
	using base::erase;

	using base::begin;
	using base::end;
	using base::rbegin;
	using base::rend;

	using base::empty;
	using base::size;
	using base::max_size;

	using base::find;
	using base::count;
	using base::lower_bound;
	using base::upper_bound;
	using base::equal_range;
	using base::swap;

protected:

	using base::c;

};


/* Non-member functions.  These are at the end because they are not associated with any
   particular class.  These will be implemented as I figure out exactly what all of
   them are supposed to do, and I have time.
 */

	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator<
		(const aloneMap<Key,T,Compare,Allocator>& x, const aloneMap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator!=
		(const aloneMap<Key,T,Compare,Allocator>& x, const aloneMap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator>
		(const aloneMap<Key,T,Compare,Allocator>& x, const aloneMap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator>=
		(const aloneMap<Key,T,Compare,Allocator>& x, const aloneMap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator<=
		(const aloneMap<Key,T,Compare,Allocator>& x, const aloneMap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT void swap
		(aloneMap<Key,T,Compare,Allocator>& x, aloneMap<Key,T,Compare,Allocator>& y);


	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator==
		(const aloneMultimap<Key,T,Compare,Allocator>& x, const aloneMultimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator<
		(const aloneMultimap<Key,T,Compare,Allocator>& x, const aloneMultimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator!=
		(const aloneMultimap<Key,T,Compare,Allocator>& x, const aloneMultimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator>
		(const aloneMultimap<Key,T,Compare,Allocator>& x, const aloneMultimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator>=
		(const aloneMultimap<Key,T,Compare,Allocator>& x, const aloneMultimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT bool operator<=
		(const aloneMultimap<Key,T,Compare,Allocator>& x, const aloneMultimap<Key,T,Compare,Allocator>& y);
	template <class Key, class T, class Compare, class Allocator> _UCXXEXPORT void swap
		(aloneMultimap<Key,T,Compare,Allocator>& x, aloneMultimap<Key,T,Compare,Allocator>& y);

}

#pragma GCC visibility pop

#endif
