
template <class _RanIt, class _Pr>
inline void sort(const _RanIt _First, const _RanIt _Last, _Pr _Pred) { // order [_First, _Last), using _Pred
    _Adl_verify_range(_First, _Last);
    const auto _UFirst = _Get_unwrapped(_First);
    const auto _ULast  = _Get_unwrapped(_Last);
    _Sort_unchecked(_UFirst, _ULast, _ULast - _UFirst, _Pass_fn(_Pred));
}

template <class _RanIt>
inline void sort(const _RanIt _First, const _RanIt _Last) { // order [_First, _Last), using operator<
    _STD sort(_First, _Last, less<>());
}


template <class _Iter, class _Sentinel>
constexpr void _Adl_verify_range(
    const _Iter& _First, const _Sentinel& _Last) { // check that [_First, _Last) forms an iterator range
    if constexpr (_Range_verifiable_v<_Iter, _Sentinel>) {
        _Verify_range(_First, _Last);
    } else {
        (void) _First; // TRANSITION, VSO#486357
        (void) _Last; // TRANSITION, VSO#486357
    }
}


template <class _BidIt, class _BidIt2, enable_if_t<_Range_verifiable_v<_BidIt, _BidIt2>, int> = 0>
constexpr void _Verify_range(const reverse_iterator<_BidIt>& _First, const reverse_iterator<_BidIt2>& _Last) {
    // TRANSITION, VSO#612785
    _Verify_range(_Last.base(), _First.base()); // note reversed parameters
}


template <class _RanIt, class _Pr>
inline void _Sort_unchecked(_RanIt _First, _RanIt _Last, _Iter_diff_t<_RanIt> _Ideal, _Pr _Pred) 
    { // order [_First, _Last), using _Pred
    _Iter_diff_t<_RanIt> _Count;
    while (_ISORT_MAX < (_Count = _Last - _First) && 0 < _Ideal) { // divide and conquer by quicksort
        
        auto _Mid = _Partition_by_median_guess_unchecked(_First, _Last, _Pred);
        
        // TRANSITION, VSO#433486
        _Ideal = (_Ideal >> 1) + (_Ideal >> 2); // allow 1.5 log2(N) divisions

        if (_Mid.first - _First < _Last - _Mid.second) { // loop on second half
            _Sort_unchecked(_First, _Mid.first, _Ideal, _Pred);
            _First = _Mid.second;
        } else { // loop on first half
            _Sort_unchecked(_Mid.second, _Last, _Ideal, _Pred);
            _Last = _Mid.first;
        }
    }

    if (_ISORT_MAX < _Count) { // heap sort if too many divisions
        _Make_heap_unchecked(_First, _Last, _Pred);
        _Sort_heap_unchecked(_First, _Last, _Pred);
    } else if (2 <= _Count) { 
        _Insertion_sort_unchecked(_First, _Last, _Pred); // small
    }
} 

const int _ISORT_MAX = 32; // maximum size for insertion sort

template <class _RanIt, class _Pr>
inline pair<_RanIt, _RanIt> _Partition_by_median_guess_unchecked(
    _RanIt _First, _RanIt _Last, _Pr _Pred) 
    { // partition [_First, _Last), using _Pred
    _RanIt _Mid = _First + ((_Last - _First) >> 1); // TRANSITION, VSO#433486
    //중간값
    _Guess_median_unchecked(_First, _Mid, _Last - 1, _Pred);
    _RanIt _Pfirst = _Mid;
    _RanIt _Plast  = _Pfirst + 1;

    while (_First < _Pfirst && !_DEBUG_LT_PRED(_Pred, *(_Pfirst - 1), *_Pfirst) && !_Pred(*_Pfirst, *(_Pfirst - 1))) {
        --_Pfirst;
    }

    while (_Plast < _Last && !_DEBUG_LT_PRED(_Pred, *_Plast, *_Pfirst) && !_Pred(*_Pfirst, *_Plast)) {
        ++_Plast;
    }

    _RanIt _Gfirst = _Plast;
    _RanIt _Glast  = _Pfirst;

    for (;;) { // partition
        for (; _Gfirst < _Last; ++_Gfirst) {
            if (_DEBUG_LT_PRED(_Pred, *_Pfirst, *_Gfirst)) {
            } else if (_Pred(*_Gfirst, *_Pfirst)) {
                break;
            } else if (_Plast != _Gfirst) {
                _STD iter_swap(_Plast, _Gfirst);
                ++_Plast;
            } else {
                ++_Plast;
            }
        }

        for (; _First < _Glast; --_Glast) {
            if (_DEBUG_LT_PRED(_Pred, *(_Glast - 1), *_Pfirst)) {
            } else if (_Pred(*_Pfirst, *(_Glast - 1))) {
                break;
            } else if (--_Pfirst != _Glast - 1) {
                _STD iter_swap(_Pfirst, _Glast - 1);
            }
        }

        if (_Glast == _First && _Gfirst == _Last) {
            return pair<_RanIt, _RanIt>(_Pfirst, _Plast);
        }

        if (_Glast == _First) { // no room at bottom, rotate pivot upward
            if (_Plast != _Gfirst) {
                _STD iter_swap(_Pfirst, _Plast);
            }

            ++_Plast;
            _STD iter_swap(_Pfirst, _Gfirst);
            ++_Pfirst;
            ++_Gfirst;
        } else if (_Gfirst == _Last) { // no room at top, rotate pivot downward
            if (--_Glast != --_Pfirst) {
                _STD iter_swap(_Glast, _Pfirst);
            }

            _STD iter_swap(_Pfirst, --_Plast);
        } else {
            _STD iter_swap(_Gfirst, --_Glast);
            ++_Gfirst;
        }
    }
}


template <class _RanIt, class _Pr>
inline void _Guess_median_unchecked(
    _RanIt _First, _RanIt _Mid, _RanIt _Last, _Pr _Pred) 
    { // sort median element to middle
    using _Diff        = _Iter_diff_t<_RanIt>;
    const _Diff _Count = _Last - _First;
    if (40 < _Count) { // median of nine
        const _Diff _Step     = (_Count + 1) >> 3; // +1 can't overflow because range was made inclusive in caller
        const _Diff _Two_step = _Step << 1; // note: intentionally discards low-order bit
        _Med3_unchecked(_First, _First + _Step, _First + _Two_step, _Pred);
        _Med3_unchecked(_Mid - _Step, _Mid, _Mid + _Step, _Pred);
        _Med3_unchecked(_Last - _Two_step, _Last - _Step, _Last, _Pred);
        _Med3_unchecked(_First + _Step, _Mid, _Last - _Step, _Pred);
    } else {
        _Med3_unchecked(_First, _Mid, _Last, _Pred);
    }
}

#define _DEBUG_LT_PRED(pred, x, y) pred(x, y)

template <class _RanIt, class _Pr>
inline void _Med3_unchecked(_RanIt _First, _RanIt _Mid, _RanIt _Last, _Pr _Pred) 
{ // sort median of three elements to middle
    if (_DEBUG_LT_PRED(_Pred, *_Mid, *_First)) {
        _STD iter_swap(_Mid, _First);
    }

    if (_DEBUG_LT_PRED(_Pred, *_Last, *_Mid)) { // swap middle and last, then test first again
        _STD iter_swap(_Last, _Mid);

        if (_DEBUG_LT_PRED(_Pred, *_Mid, *_First)) {
            _STD iter_swap(_Mid, _First);
        }
    }
}


// FUNCTION TEMPLATE sort
template <class _BidIt, class _Pr>
inline _BidIt _Insertion_sort_unchecked(
    _BidIt _First, const _BidIt _Last, _Pr _Pred) { // insertion sort [_First, _Last), using _Pred
    if (_First != _Last) {
        for (_BidIt _Next = _First; ++_Next != _Last;) { // order next element
            _BidIt _Next1              = _Next;
            _Iter_value_t<_BidIt> _Val = _STD move(*_Next);

            if (_DEBUG_LT_PRED(_Pred, _Val, *_First)) { // found new earliest element, move to front
                _Move_backward_unchecked(_First, _Next, ++_Next1);
                *_First = _STD move(_Val);
            } else { // look for insertion point after first
                for (_BidIt _First1 = _Next1; _DEBUG_LT_PRED(_Pred, _Val, *--_First1); _Next1 = _First1) {
                    *_Next1 = _STD move(*_First1); // move hole down
                }

                *_Next1 = _STD move(_Val); // insert element in hole
            }
        }
    }

    return _Last;
}




// FUNCTION TEMPLATE make_heap
template <class _RanIt, class _Pr>
inline void _Make_heap_unchecked(
    _RanIt _First, _RanIt _Last, _Pr _Pred) { // make nontrivial [_First, _Last) into a heap, using _Pred
    _Iter_diff_t<_RanIt> _Bottom = _Last - _First;
    for (_Iter_diff_t<_RanIt> _Hole = _Bottom >> 1; 0 < _Hole;) // TRANSITION, VSO#433486
    { // reheap top half, bottom to top
        --_Hole;
        _Iter_value_t<_RanIt> _Val = _STD move(*(_First + _Hole));
        _Pop_heap_hole_by_index(_First, _Hole, _Bottom, _STD move(_Val), _Pred);
    }
}


// FUNCTION TEMPLATE sort_heap
template <class _RanIt, class _Pr>
inline void _Sort_heap_unchecked(
    _RanIt _First, _RanIt _Last, _Pr _Pred) { // order heap by repeatedly popping, using _Pred
    for (; 2 <= _Last - _First; --_Last) {
        _Pop_heap_unchecked(_First, _Last, _Pred);
    }
}


template <class _RanIt, class _Pr>
inline void _Pop_heap_unchecked(
    _RanIt _First, _RanIt _Last, _Pr _Pred) { // pop *_First to *(_Last - 1) and reheap, using _Pred
    if (2 <= _Last - _First) {
        --_Last;
        _Iter_value_t<_RanIt> _Val = _STD move(*_Last);
        _Pop_heap_hole_unchecked(_First, _Last, _Last, _STD move(_Val), _Pred);
    }
}
