using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DesignPatternExamples_csharp
{
    internal interface ISortEntries
    {
        void Sort(List<EntryInformation> entries);
    }

    class Strategy_SortEntries_Base
    {
        public void Sort(List<EntryInformation> entries, Comparison<EntryInformation> comparison)
        {
            entries.Sort(comparison);
            foreach (EntryInformation entry in entries)
            {
                if (entry.Children != null)
                {
                    Sort(entry.Children, comparison);
                }
            }
        }
    }


    internal class Strategy_SortEntries_ByName : Strategy_SortEntries_Base, ISortEntries
    {
        bool _reversedSort;

        public Strategy_SortEntries_ByName(bool reversedSort)
        {
            _reversedSort = reversedSort;
        }


        public void Sort(List<EntryInformation> entries)
        {
            base.Sort(entries, delegate (EntryInformation left, EntryInformation right)
            {
                return (_reversedSort) ? right.Name.CompareTo(left.Name) : left.Name.CompareTo(right.Name);
            });
        }
    }

    internal class Strategy_SortEntries_ByLastModified : Strategy_SortEntries_Base, ISortEntries
    {
        bool _reversedSort;

        public Strategy_SortEntries_ByLastModified(bool reversedSort)
        {
            _reversedSort = reversedSort;
        }


        public void Sort(List<EntryInformation> entries)
        {
            base.Sort(entries, delegate (EntryInformation left, EntryInformation right)
            {
                return (_reversedSort) ? right.LastModified.CompareTo(left.LastModified) : left.LastModified.CompareTo(right.LastModified);
            });
        }
    }

    internal class Strategy_SortEntries_ByWhenCreated : Strategy_SortEntries_Base, ISortEntries
    {
        bool _reversedSort;

        public Strategy_SortEntries_ByWhenCreated(bool reversedSort)
        {
            _reversedSort = reversedSort;
        }


        public void Sort(List<EntryInformation> entries)
        {
            base.Sort(entries, delegate (EntryInformation left, EntryInformation right)
            {
                return (_reversedSort) ? right.WhenCreated.CompareTo(left.WhenCreated) : left.WhenCreated.CompareTo(right.WhenCreated);
            });
        }
    }

    internal class Strategy_SortEntries_ByLastAccessed : Strategy_SortEntries_Base, ISortEntries
    {
        bool _reversedSort;

        public Strategy_SortEntries_ByLastAccessed(bool reversedSort)
        {
            _reversedSort = reversedSort;
        }


        public void Sort(List<EntryInformation> entries)
        {
            base.Sort(entries, delegate (EntryInformation left, EntryInformation right)
            {
                return (_reversedSort) ? right.LastAccess.CompareTo(left.LastAccess) : left.LastAccess.CompareTo(right.LastAccess);
            });
        }
    }

    internal class Strategy_SortEntries_BySize : Strategy_SortEntries_Base, ISortEntries
    {
        bool _reversedSort;

        public Strategy_SortEntries_BySize(bool reversedSort)
        {
            _reversedSort = reversedSort;
        }


        public void Sort(List<EntryInformation> entries)
        {
            base.Sort(entries, delegate (EntryInformation left, EntryInformation right)
            {
                return (_reversedSort) ? right.Size.CompareTo(left.Size) : left.Size.CompareTo(right.Size);
            });
        }
    }


    internal static class Strategy_SortEntries_ClassFactory
    {
        internal static ISortEntries Create(InputOptions options)
        {
            ISortEntries sortEntries = null;

            switch(options.SortOptions)
            {
                case SortOptions.ByName:
                    sortEntries = new Strategy_SortEntries_ByName(options.ReverseSort);
                    break;

                case SortOptions.ByLastModified:
                    sortEntries = new Strategy_SortEntries_ByLastModified(options.ReverseSort);
                    break;

                case SortOptions.ByWhenCreated:
                    sortEntries = new Strategy_SortEntries_ByWhenCreated(options.ReverseSort);
                    break;

                case SortOptions.ByLastAccess:
                    sortEntries = new Strategy_SortEntries_ByLastAccessed(options.ReverseSort);
                    break;

                case SortOptions.BySize:
                    sortEntries = new Strategy_SortEntries_BySize(options.ReverseSort);
                    break;

                default:
                    {
                        string message = string.Format("Unrecognized sort option: {0}", options.SortOptions);
                        throw new ApplicationException(message);
                    }
            }

            return sortEntries;
        }
    }
}
