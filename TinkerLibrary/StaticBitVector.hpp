//
//  StaticBitVector.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-9-18.
//  Copyright © 2020 FireWolf. All rights reserved.
//

#ifndef StaticBitVector_hpp
#define StaticBitVector_hpp

#include "BitOptions.hpp"
#include "BitMasks.hpp"
#include "ClosedRange.hpp"

///
/// A static bit vector manages a fixed number of bit values, either 0 or 1.
/// Internally, it maintains a static array of `BitOptions<size_t>` by default.
/// On 32-bit system, each element in the array is 4 bytes long, while 8 bytes long on 64-bit system.
/// The caller could also override such behavior and specify another underlying storage type to save memory.
//
/// @tparam NumBits Specify the total number of bits
/// @tparam StorageUnit Specify the underlying integer type to store bits
///
template <size_t NumBits, typename StorageUnit = size_t>
requires std::unsigned_integral<StorageUnit>
class StaticBitVector
{
private:
    /// Compile time constant that stores the number of bits stored in each `BitOptions` block
    static constexpr size_t NumBitsPerOptionsBlock = sizeof(StorageUnit) * 8;

    /// Compile time constant that stores the number of unused bits in the last `BitOptions` block
    static constexpr size_t NumUnusedBits = NumBitsPerOptionsBlock - NumBits % NumBitsPerOptionsBlock;

    /// Compile time constant that stores the number of used bits in the last `BitOptions` block
    static constexpr size_t NumUsedBits = NumBits % NumBitsPerOptionsBlock;

    /// Compile time constant that stores the bit mask to zero out unused bits in the last block
    static constexpr StorageUnit LastBlockUnusedBitMask = (static_cast<StorageUnit>(1) << NumUsedBits) - 1;

    /// Compile time constant that stores the actual number of options
    static constexpr size_t NumOptionsBlocks = (NumBits / NumBitsPerOptionsBlock) + (NumUsedBits ? 1 : 0);

    /// The internal storage
    BitOptions<StorageUnit> blocks[NumOptionsBlocks];

    ///
    /// Retrieve the block and the offset from the given bit index
    ///
    /// @param index The bit index
    /// @param block The block index on return
    /// @param offset The offset into the `block` on return
    /// @return `true` if the given index is valid, `false` otherwise.
    ///
    inline bool index2BlockOffset(size_t index, size_t& block, size_t& offset) const
    {
        // Guard: Ensure that the index is not out-of-bound
        if (index >= NumBits)
        {
            return false;
        }

        // Retrieve the block number and the offset in that block
        block = index / NumBitsPerOptionsBlock;

        offset = index % NumBitsPerOptionsBlock;

        return true;
    }

#ifdef DEBUG
    friend class StaticBitVectorTest;
#endif

public:
    // MARK: Create / Initialize a Bit Vector

    /// Initialize the bit vector with all zeros
    void initWithZeros()
    {
        pinfo("Initialized with NumBits = %lu; Storage Unit Size = %lu; NumOptions = %lu; Storage Size = %lu.", NumBits, sizeof(StorageUnit), NumOptionsBlocks, sizeof(this->blocks));

        for (auto& block : this->blocks)
        {
            block.clearAll();
        }
    }

    /// Initialize the bit vector with all ones
    void initWithOnes()
    {
        pinfo("Initialized with NumBits = %lu; Storage Unit Size = %lu; NumOptions = %lu; Storage Size = %lu.", NumBits, sizeof(StorageUnit), NumOptionsBlocks, sizeof(this->blocks));

        for (auto& block : this->blocks)
        {
            block.setAll();
        }

        // Zero out "nonexistent" bits
        if (NumUnusedBits != 0)
        {
            //pinfo("NumUnusedBits = %lu; LastBlockValue = 0x%llu; LastBlockMask = 0x%llu.",
            //      NumUnusedBits, this->blocks[NumOptionsBlocks - 1].flatten(), LastBlockUnusedBitMask);

            this->blocks[NumOptionsBlocks - 1].mutativeBitwiseAnd(LastBlockUnusedBitMask);
        }
    }

//    ///
//    /// Create a fixed size bit vector with all zeros
//    ///
//    /// @param allocator The allocator used to allocate an instance of bit vector
//    /// @return A bit vector with all bit values set to zero, `NULL` if no memory.
//    /// @note The caller is responsible for releasing the returned object.
//    ///
//    static StaticBitVector* createWithZeros(MemoryAllocator* allocator)
//    {
//        StaticBitVector* instance = allocator->allocate(sizeof(StaticBitVector));
//
//        if (instance != nullptr)
//        {
//            instance->initWithZeros();
//        }
//
//        return instance;
//    }
//
//    ///
//    /// Create a fixed size bit vector with all ones
//    ///
//    /// @param allocator The allocator used to allocate an instance of bit vector
//    /// @return A bit vector with all bit values set to one, `NULL` if no memory.
//    /// @note The caller is responsible for releasing the returned object.
//    ///
//    static StaticBitVector* createWithOnes(MemoryAllocator* allocator)
//    {
//        auto* instance = reinterpret_cast<StaticBitVector*>(allocator->allocate(sizeof(StaticBitVector)));
//
//        if (instance != nullptr)
//        {
//            instance->initWithOnes();
//        }
//
//        return instance;
//    }

    // MARK: Examine a bit in the vector

    ///
    /// Check whether the given bit is set in the vector
    ///
    /// @param index Index of the bit
    /// @return `true` if the bit at the given index is set, `false` otherwise.
    /// @warning The given index must be less than the total number of bits, otherwise `false` is returned.
    ///
    [[nodiscard]]
    inline bool containsBit(size_t index) const
    {
        size_t block = 0, offset = 0;

        // Guard: Verify the index and retrieve the block number and the offset
        if (!this->index2BlockOffset(index, block, offset))
        {
            return false;
        }

        // Check the bit
        return this->blocks[block].containsBit(offset);
    }

    ///
    /// Get the bit at the given index
    ///
    /// @param index Index of the bit
    /// @return The bit at the given index.
    /// @warning This function returns 0 if the given index is invalid.
    ///
    [[nodiscard]]
    inline uint8_t getBit(size_t index) const
    {
        size_t block = 0, offset = 0;

        // Guard: Verify the index and retrieve the block number and the offset
        if (!this->index2BlockOffset(index, block, offset))
        {
            return 0;
        }

        // Get the bit
        return this->blocks[block].getBit(offset);
    }

    ///
    /// Set the bit at the given index
    ///
    /// @param index Index of the bit
    /// @warning This function has no effect if the given index is invalid.
    ///
    inline void setBit(size_t index)
    {
        size_t block = 0, offset = 0;

        // Guard: Verify the index and retrieve the block number and the offset
        if (this->index2BlockOffset(index, block, offset))
        {
            // Set the bit
            this->blocks[block].setBit(offset);
        }
    }

    ///
    /// Clear the bit at the given index
    ///
    /// @param index Index of the bit
    /// @warning This function has no effect if the given index is invalid.
    ///
    inline void clearBit(size_t index)
    {
        size_t block = 0, offset = 0;

        // Guard: Verify the index and retrieve the block number and the offset
        if (this->index2BlockOffset(index, block, offset))
        {
            // Clear the bit
            this->blocks[block].clearBit(offset);
        }
    }

    ///
    /// Find the position of the least significant bit
    ///
    /// @return Index of the least significant bit.
    /// @warning This function returns -1 if no such bit exists.
    ///
    [[nodiscard]]
    ssize_t findLeastSignificantBitIndex() const
    {
        // Block Array:
        // --- Block 0 --- | --- Block 1 --- | ... | --- Block N --- |
        // _ _ _ _ _ _ _ _ | _ _ _ _ _ _ _ _ |
        // 7 6 5 4 3 2 1 0   F E D C B A 9 8 |
        for (size_t index = 0; index < NumOptionsBlocks; index += 1)
        {
            // Guard: Skip the current block if it is empty
            if (this->blocks[index].isEmpty())
            {
                continue;
            }

            // The current block is not empty
            // Retrieve the index of the LSB in this block
            uint32_t offset = this->blocks[index].findLeastSignificantBitIndex();

            return index * NumBitsPerOptionsBlock + offset;
        }

        // Not found
        return -1;
    }

    ///
    /// Find the position of the least significant bit in the given range
    ///
    /// @param range Specify the range when searching for the least significant bit
    /// @return The absolute index of the least significant bit on success, `-1` if no such bit exists.
    ///
    template <typename Bound = size_t> [[nodiscard]]
    ssize_t findLeastSignificantBitIndexWithRange(ClosedRange<Bound> range) const
    {
        // Block Array:
        // --- Block 0 --- | --- Block 1 --- | ... | --- Block N --- |
        // _ _ _ _ _ _ _ _ | _ _ _ _ _ _ _ _ |
        // 7 6 5 4 3 2 1 0   F E D C B A 9 8 |
        // Supposed that the range is [5, 12],
        // First find the first block and the last block in the range.
        size_t fblock, foffset;

        size_t lblock, loffset;

        if (!this->index2BlockOffset(range.lowerBound, fblock, foffset))
        {
            perr("The lower bound %lu of the given range [%lu, %lu] is not valid.", range.lowerBound, range.lowerBound, range.upperBound);

            return -1;
        }

        if (!this->index2BlockOffset(range.upperBound, lblock, loffset))
        {
            perr("The upper bound %lu of the given range [%lu, %lu] is not valid.", range.upperBound, range.lowerBound, range.upperBound);

            return -1;
        }

        // Guard: Check whether the first and the last block are the same
        if (fblock == lblock)
        {
            StorageUnit mask = BitMask<StorageUnit>::createWithRangeOfBitsSet({foffset, loffset});

            BitOptions<StorageUnit> options = this->blocks[fblock].bitwiseAnd(mask);

            if (options.isEmpty())
            {
                return -1;
            }
            else
            {
                return fblock * NumBitsPerOptionsBlock + options.findLeastSignificantBitIndex();
            }
        }

        // Then make a copy of these two blocks and clear out-of-bounds bits
        // --- Block 0 --- | --- Block 1 --- | ... | --- Block N --- |
        // _ _ _ _ _ _ _ _ | _ _ _ _ _ _ _ _ |
        // 7 6 5 4 3 2 1 0   F E D C B A 9 8 |
        // ~~~~~                   ~~~~~~~~~
        // 1 1 1 0 0 0 0 0 | 0 0 0 1 1 1 1 1   <- Bit Mask
        // Lower Bound @ Block Index = 0, Offset = 5: Mask = ~((1 << 5) - 1) = 0b11100000; i.e. Clear low 5 bits.
        // Upper Bound @ Block Index = 1, Offset = 4: Mask = (1 << (4 + 1) - 1) = 0b00011111; i.e. Set low 4 + 1 bits.
        StorageUnit fMask = BitMask<StorageUnit>::createWithLowBitsClear(foffset); //~((static_cast<StorageUnit>(1) << foffset) - 1);

        StorageUnit lMask = BitMask<StorageUnit>::createWithLowBitsSet(loffset + 1); //(static_cast<StorageUnit>(1) << (loffset + 1)) - 1;

        BitOptions<StorageUnit> fOptions = this->blocks[fblock].bitwiseAnd(fMask);

        BitOptions<StorageUnit> lOptions = this->blocks[lblock].bitwiseAnd(lMask);

        // Finally treat the first and the last block specially when searching for the LSB
        if (!fOptions.isEmpty())
        {
            // The LSB is in the first block
            return fblock * NumBitsPerOptionsBlock + fOptions.findLeastSignificantBitIndex();
        }

        for (size_t index = fblock + 1; index < lblock - 1; index += 1)
        {
            // Guard: Skip empty middle blocks
            if (this->blocks[index].isEmpty())
            {
                continue;
            }

            // The LSB is in the current block
            return index * NumBitsPerOptionsBlock + this->blocks[index].findLeastSignificantBitIndex();
        }

        if (!lOptions.isEmpty())
        {
            // The LSB is in the last block
            return lblock * NumBitsPerOptionsBlock + lOptions.findLeastSignificantBitIndex();
        }

        // Not found
        return -1;
    }

    ///
    /// Find the position of the most significant bit
    ///
    /// @return Index of the most significant bit.
    /// @warning This function returns -1 if no such bit exists.
    ///
    [[nodiscard]]
    ssize_t findMostSignificantBitIndex() const
    {
        for (size_t index = NumOptionsBlocks - 1; index >= 0; index -= 1)
        {
            // Guard: Skip the current block if it is empty
            if (this->blocks[index].isEmpty())
            {
                continue;
            }

            // The current block is not empty
            // Retrieve the index of the MSB in this block
            uint32_t offset = this->blocks[index].findMostSignificantBitIndex();

            return index * NumBitsPerOptionsBlock + offset;
        }

        // Not found
        return -1;
    }

    ///
    /// Find the position of the most significant bit in the given range
    ///
    /// @param range Specify the range when searching for the most significant bit
    /// @return The absolute index of the most significant bit on success, `-1` if no such bit exists.
    ///
    template <typename Bound = size_t> [[nodiscard]]
    ssize_t findMostSignificantBitIndexWithRange(ClosedRange<Bound> range) const
    {
        // Block Array:
        // --- Block 0 --- | --- Block 1 --- | ... | --- Block N --- |
        // _ _ _ _ _ _ _ _ | _ _ _ _ _ _ _ _ |
        // 7 6 5 4 3 2 1 0   F E D C B A 9 8 |
        // Supposed that the range is [5, 12],
        // First find the first block and the last block in the range.
        size_t fblock, foffset;

        size_t lblock, loffset;

        if (!this->index2BlockOffset(range.lowerBound, fblock, foffset))
        {
            perr("The lower bound %lu of the given range [%lu, %lu] is not valid.", range.lowerBound, range.lowerBound, range.upperBound);

            return -1;
        }

        if (!this->index2BlockOffset(range.upperBound, lblock, loffset))
        {
            perr("The upper bound %lu of the given range [%lu, %lu] is not valid.", range.upperBound, range.lowerBound, range.upperBound);

            return -1;
        }

        // Guard: Check whether the first and the last block are the same
        if (fblock == lblock)
        {
            StorageUnit mask = BitMask<StorageUnit>::createWithRangeOfBitsSet({foffset, loffset});

            BitOptions<StorageUnit> options = this->blocks[fblock].bitwiseAnd(mask);

            if (options.isEmpty())
            {
                return -1;
            }
            else
            {
                return fblock * NumBitsPerOptionsBlock + options.findMostSignificantBitIndex();
            }
        }

        // Then make a copy of these two blocks and clear out-of-bounds bits
        // --- Block 0 --- | --- Block 1 --- | ... | --- Block N --- |
        // _ _ _ _ _ _ _ _ | _ _ _ _ _ _ _ _ |
        // 7 6 5 4 3 2 1 0   F E D C B A 9 8 |
        // ~~~~~                   ~~~~~~~~~
        // 1 1 1 0 0 0 0 0 | 0 0 0 1 1 1 1 1   <- Bit Mask
        // Lower Bound @ Block Index = 0, Offset = 5: Mask = ~((1 << 5) - 1) = 0b11100000
        // Upper Bound @ Block Index = 1, Offset = 4: Mask = (1 << (4 + 1)) - 1 = 0b00011111
        StorageUnit fMask = ~((static_cast<StorageUnit>(1) << foffset) - 1);

        StorageUnit lMask = (static_cast<StorageUnit>(1) << (loffset + 1)) - 1;

        BitOptions<StorageUnit> fOptions = this->blocks[fblock].bitwiseAnd(fMask);

        BitOptions<StorageUnit> lOptions = this->blocks[lblock].bitwiseAnd(lMask);

        // Finally treat the first and the last block specially when searching for the MSB
        if (!lOptions.isEmpty())
        {
            // The LSB is in the last block
            return lblock * NumBitsPerOptionsBlock + lOptions.findMostSignificantBitIndex();
        }

        for (size_t index = lblock - 1; index >= fblock + 1; index -= 1)
        {
            // Guard: Skip empty middle blocks
            if (this->blocks[index].isEmpty())
            {
                continue;
            }

            // The LSB is in the current block
            return index * NumBitsPerOptionsBlock + this->blocks[index].findMostSignificantBitIndex();
        }

        if (!fOptions.isEmpty())
        {
            // The LSB is in the first block
            return fblock * NumBitsPerOptionsBlock + fOptions.findMostSignificantBitIndex();
        }

        // Not found
        return -1;
    }
};

#endif /* StaticBitVector_hpp */
