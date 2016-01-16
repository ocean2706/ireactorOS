/*
 * Copyright 2011, Jérôme Duval, korli@users.berlios.de.
 * Copyright 2008, Axel Dörfler, axeld@pinc-software.de.
 * This file may be used under the terms of the MIT License.
 */
#ifndef INODE_H
#define INODE_H


#include <fs_cache.h>
#include <lock.h>
#include <string.h>

#include "btrfs.h"
#include "Volume.h"


//#define TRACE_BTRFS
#ifdef TRACE_BTRFS
#	define TRACEI(x...) dprintf("\33[34mbtrfs:\33[0m " x)
#else
#	define TRACEI(x...) ;
#endif


class Inode {
public:
						Inode(Volume* volume, ino_t id);
						~Inode();

			status_t	InitCheck();

			ino_t		ID() const { return fID; }

			rw_lock*	Lock() { return &fLock; }

			status_t	UpdateNodeFromDisk();

			bool		IsDirectory() const
							{ return S_ISDIR(Mode()); }
			bool		IsFile() const
							{ return S_ISREG(Mode()); }
			bool		IsSymLink() const
							{ return S_ISLNK(Mode()); }
			status_t	CheckPermissions(int accessMode) const;

			mode_t		Mode() const { return fNode.Mode(); }
			off_t		Size() const { return fNode.Size(); }
			uid_t		UserID() const { return fNode.UserID(); }
			gid_t		GroupID() const { return fNode.GroupID(); }
			void		GetChangeTime(struct timespec &timespec) const
							{ fNode.GetChangeTime(timespec); }
			void		GetModificationTime(struct timespec &timespec) const
							{ fNode.GetModificationTime(timespec); }
			void		GetCreationTime(struct timespec &timespec) const
							{ fNode.GetCreationTime(timespec); }
			void		GetAccessTime(struct timespec &timespec) const
							{ fNode.GetCreationTime(timespec); }

			Volume*		GetVolume() const { return fVolume; }

			status_t	FindBlock(off_t logical, off_t& physical,
							off_t *_length = NULL);
			status_t	ReadAt(off_t pos, uint8 *buffer, size_t *length);
			status_t	FillGapWithZeros(off_t start, off_t end);

			void*		FileCache() const { return fCache; }
			void*		Map() const { return fMap; }
			
			status_t	FindParent(ino_t *id);
private:
						Inode(Volume* volume);
						Inode(const Inode&);
						Inode &operator=(const Inode&);
							// no implementation

			uint64		_NumBlocks();

			rw_lock		fLock;
			::Volume*	fVolume;
			ino_t		fID;
			void*		fCache;
			void*		fMap;
			status_t	fInitStatus;
			struct btrfs_inode fNode;
};


// The Vnode class provides a convenience layer upon get_vnode(), so that
// you don't have to call put_vnode() anymore, which may make code more
// readable in some cases

class Vnode {
public:
	Vnode(Volume* volume, ino_t id)
		:
		fInode(NULL)
	{
		SetTo(volume, id);
	}

	Vnode()
		:
		fStatus(B_NO_INIT),
		fInode(NULL)
	{
	}

	~Vnode()
	{
		Unset();
	}

	status_t InitCheck()
	{
		return fStatus;
	}

	void Unset()
	{
		if (fInode != NULL) {
			put_vnode(fInode->GetVolume()->FSVolume(), fInode->ID());
			fInode = NULL;
			fStatus = B_NO_INIT;
		}
	}

	status_t SetTo(Volume* volume, ino_t id)
	{
		Unset();

		return fStatus = get_vnode(volume->FSVolume(), id, (void**)&fInode);
	}

	status_t Get(Inode** _inode)
	{
		*_inode = fInode;
		return fStatus;
	}

	void Keep()
	{
		TRACEI("Vnode::Keep()\n");
		fInode = NULL;
	}

private:
	status_t	fStatus;
	Inode*		fInode;
};

#endif	// INODE_H
